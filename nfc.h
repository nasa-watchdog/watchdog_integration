/**
 * @file quick_start_example1.c
 * @brief Quick start example that presents how to use libnfc
 */

// To compile this simple example:
// $ gcc -o quick_start_example1 quick_start_example1.c -lnfc

#include <stdlib.h>
#include <nfc/nfc.h>
#include <string.h>

static char *library[6] = {(char*)"04  22  33  3a  ed  4c  81  ",(char*)"04  81  1f  3a  ed  4c  80  ",(char*)")04  7b  1d  3a  ed  4c  80  ",(char*)"04  c8  25  3a  ed  4c  80  ",(char*)"04  53  36  3a  ed  4c  81  ",(char*)"04  5b  36  3a  ed  4c  81  "};

static void
print_hex(const uint8_t *pbtData, const size_t szBytes)
{
  size_t  szPos;

  for (szPos = 0; szPos < szBytes; szPos++) {
    printf("%02x  ", pbtData[szPos]);
  }
  printf("\n");
}
static int result;
static int
print_hhhex(const uint8_t *pbtData, const size_t szBytes)
{
  size_t  szPos;
  char buffer[100];
  char tmp[5];
  int n;
  //int result;
  for (szPos = 0; szPos < szBytes; szPos++) {
    n = sprintf(tmp ,"%02x  ", pbtData[szPos]);
    strcat(buffer,tmp);
  }
  //printf("%s\n",buffer);
  //printf("%s\n",library[1]);
  for (int i = 0; i < 6;i++){
    
    if (strcmp(library[i],buffer)==0){
      result = i;
      //printf("%d", result);

    }
  }
  return result;
}

int
NFCresult()
{
  nfc_device *pnd;
  nfc_target nt;
  FILE *JSON;
  int x; 
  // Allocate only a pointer to nfc_context
  nfc_context *context;

  // Initialize libnfc and set the nfc_context
  nfc_init(&context);
  if (context == NULL) {
    printf("Unable to init libnfc (malloc)\n");
    exit(EXIT_FAILURE);
  }

  // Display libnfc version
  const char *acLibnfcVersion = nfc_version();
  //(void)argc;
  //printf("%s uses libnfc %s\n", argv[0], acLibnfcVersion);

  // Open, using the first available NFC device which can be in order of selection:
  //   - default device specified using environment variable or
  //   - first specified device in libnfc.conf (/etc/nfc) or
  //   - first specified device in device-configuration directory (/etc/nfc/devices.d) or
  //   - first auto-detected (if feature is not disabled in libnfc.conf) device
  pnd = nfc_open(context, NULL);

  if (pnd == NULL) {
    printf("ERROR: %s\n", "Unable to open NFC device.");
    exit(EXIT_FAILURE);
  }
  // Set opened NFC device to initiator mode
  if (nfc_initiator_init(pnd) < 0) {
    nfc_perror(pnd, "nfc_initiator_init");
    exit(EXIT_FAILURE);
  }

  //printf("NFC reader: %s opened\n", nfc_device_get_name(pnd));

  // Poll for a ISO14443A (MIFARE) tag
  const nfc_modulation nmMifare[1] = {
    {.nmt = NMT_ISO14443A,
    .nbr = NBR_106},
  };

  const nfc_modulation nmModulations[5] = {
    { .nmt = NMT_ISO14443A, .nbr = NBR_106 },
    { .nmt = NMT_ISO14443B, .nbr = NBR_106 },
    { .nmt = NMT_FELICA, .nbr = NBR_212 },
    { .nmt = NMT_FELICA, .nbr = NBR_424 },
    { .nmt = NMT_JEWEL, .nbr = NBR_106 },
  };
  const size_t szModulations = 5;
  //polling will take 3s
  if (nfc_initiator_poll_target(pnd, nmMifare, 1, 1, 1, &nt) > 0) {
    printf("The following (NFC) ISO14443A tag was found:\n");
    printf("    ATQA (SENS_RES): ");
    print_hex(nt.nti.nai.abtAtqa, 2);
    printf("       UID (NFCID%c): ", (nt.nti.nai.abtUid[0] == 0x08 ? '3' : '1'));

    x = print_hhhex(nt.nti.nai.abtUid, nt.nti.nai.szUidLen);
    printf("%d\n",x);
    //printf("      SAK (SEL_RES): ");
    print_hex(&nt.nti.nai.btSak, 1);
    if (nt.nti.nai.szAtsLen) {
      //printf("          ATS (ATR): ");
      print_hex(nt.nti.nai.abtAts, nt.nti.nai.szAtsLen);
    }
  }
  else{
    //nfc_perror(pnd, "nfc_initiator_poll_target");
    nfc_close(pnd);
    nfc_exit(context);
    return -1;
  }
  // Close NFC device
  nfc_close(pnd);
  // Release the context
  nfc_exit(context);
  return x;
  exit(EXIT_SUCCESS);
}

void run_nfc(int &out){
  out = NFCresult();
}
