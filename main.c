#include <windows.h>
#include <stdio.h>

// VirtualBox registry keys are reliable VM detection points because:
// 1. They exist by default in VirtualBox installations
// 2. Rarely present on physical machines
// 3. Common across versions VBoxGuest, VBoxService, etc

void vm_detected(){
    /*
        MessageBox                  CREATE AN WINDOWS ALERT
        the first L             DESCRIPTION OF THE ALERT
        the second L            TITLE OF THE ALERT
    */
    MessageBox(NULL, L"VirtualBox registry detected - VM environment", L"VM Detector", MB_OK);
    printf("[-]THIS MACHINE DOESN'T HAVE REAL PC REGEDIT");
}

void physical_machine(){
    /*
    MessageBox                  CREATE AN WINDOWS ALERT
        the first L             DESCRIPTION OF THE ALERT
        the secont L            TITLE OF THE ALERT
    */
    MessageBox(NULL, L"Real Machine Detected", L"VM Detector", MB_OK);
    printf("[-] THIS MACHINE HAS REAL PC REGEDIT.");
}


int main(){
    HKEY hKey; //THIS WILL STORAGE
    LONG result;

    /*
    [-] 'const'                    ENSURE THE REGISTRY PATH STRING WON'T BE MODIFIED ACCIDENTALLY
    [-] KEYPATCH                   STORAGES THE REGEDIT DIRECTORY PATH
    [-] ALTERNATIVE PATHS FOR VM DETECTION:
                                VBoxGuest,
                                VBoxMouse,
                                VBoxService,
                                VboxSF
                                VBoxWddm
    */
    const char* keyPatch = "SYSTEM\\CurrentControlSet\\Services\\VBoxGuest";


    /*
    [-] *RegOpenKeyExA              WINDOWS API FOR OPEN REGEDIT.
    [-] HKEY_LOCAL_MACHINE          THE ROOT DIRECTORY PATH.
    [-] '0'                         FOR RESERVED PARAMETER (DEFAULT BEHAVIOR), AS WE DON'T NEED SPECIAL OPTION LIKE REG_OPTION_VOLATILE OR REG_OPTION_BACKUP_RESTORE.
    [-] KEY_READ                    WE JUST WILL READ, NOT WRITE.
    [-] &hKEY                       THIS IS THE OUTPUT 'HANDLE' FOR THE OPENED KEY.
    */
    result = RegOpenKeyExA(HKEY_LOCAL_MACHINE, keyPatch, 0, KEY_READ, &hKey);

    if(result == ERROR_SUCCESS){
        // Key doesn't exist (likely physical machine)
        vm_detected();
        //CLOSE HANDLE OF THE REGEDIT
        RegCloseKey(hKey);
    }   else{
        physical_machine();
    }
}
