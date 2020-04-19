#include <stdio.h>
#include <switch.h>
#include <unistd.h>

u32 __nx_applet_type = AppletType_None;

#define INNER_HEAP_SIZE 0x1000
size_t nx_inner_heap_size = INNER_HEAP_SIZE;
char   nx_inner_heap[INNER_HEAP_SIZE];

void __libnx_initheap(void) {
	void*  addr = nx_inner_heap;
	size_t size = nx_inner_heap_size;

	extern char* fake_heap_start;
	extern char* fake_heap_end;

	fake_heap_start = (char *) addr;
	fake_heap_end   = (char *) addr + size;
}

void __attribute__((weak)) __appInit(void) {
    Result rc;

    rc = smInitialize();
    if (R_FAILED(rc))
        fatalThrow(MAKERESULT(Module_Libnx, LibnxError_InitFail_SM));

    rc = fsInitialize();
    if (R_FAILED(rc))
        fatalThrow(MAKERESULT(Module_Libnx, LibnxError_InitFail_FS));

    fsdevMountSdmc();
}

void __attribute__((weak)) userAppExit(void);

void __attribute__((weak)) __appExit(void) {
    fsdevUnmountAll();
    fsExit();
    smExit();
}

bool fileExists(char * path) {
    FILE * file = fopen(path, "r");
    if (file) {
        fclose(file);
        return true;
    }

    return false;
}

void deleteFile(char * path) {
    if (fileExists(path)) {
        remove(path); 
    }
}

int main(int argc, char * argv[]) {
    // Old Tesla
    deleteFile("sdmc:/atmosphere/contents/010000000007E51A/flags/boot2.flag");
    rmdir("sdmc:/atmosphere/contents/010000000007E51A/flags");
    deleteFile("sdmc:/atmosphere/contents/010000000007E51A/exefs.nsp");
    deleteFile("sdmc:/atmosphere/contents/010000000007E51A/toolbox.json");
    rmdir("sdmc:/atmosphere/contents/010000000007E51A");

    // Nichole Logo
    deleteFile("sdmc:/atmosphere/exefs_patches/nichole_logo/01890C643E9D6E17B2CDA77A9749ECB9A4F676D6000000000000000000000000.ips");
    deleteFile("sdmc:/atmosphere/exefs_patches/nichole_logo/0767302E1881700608344A3859BC57013150A375000000000000000000000000.ips");
    deleteFile("sdmc:/atmosphere/exefs_patches/nichole_logo/3EC573CB22744A993DFE281701E9CBFE66C03ABD000000000000000000000000.ips");
    deleteFile("sdmc:/atmosphere/exefs_patches/nichole_logo/723DF02F6955D903DF7134105A16D48F06012DB1000000000000000000000000.ips");
    deleteFile("sdmc:/atmosphere/exefs_patches/nichole_logo/7421EC6021AC73DD60A635BC2B3AD6FCAE2A6481000000000000000000000000.ips");
    deleteFile("sdmc:/atmosphere/exefs_patches/nichole_logo/7B4123290DE2A6F52DE4AB72BEA1A83D11214C71000000000000000000000000.ips");
    deleteFile("sdmc:/atmosphere/exefs_patches/nichole_logo/7C5894688EDA24907BC9CE7013630F365B366E4A000000000000000000000000.ips");
    deleteFile("sdmc:/atmosphere/exefs_patches/nichole_logo/967F4C3DFC7B165E4F7981373EC1798ACA234A45000000000000000000000000.ips");
    deleteFile("sdmc:/atmosphere/exefs_patches/nichole_logo/98446A07BC664573F1578F3745C928D05AB73349000000000000000000000000.ips");
    deleteFile("sdmc:/atmosphere/exefs_patches/nichole_logo/C088ADC91417EBAE6ADBDF3E47946858CAFE1A82000000000000000000000000.ips");
    deleteFile("sdmc:/atmosphere/exefs_patches/nichole_logo/C79F22F18169FCD3B3698A881394F6240385CDB1000000000000000000000000.ips");
    deleteFile("sdmc:/atmosphere/exefs_patches/nichole_logo/96529C3226BEE906EE651754C33FE3E24ECAE832000000000000000000000000.ips");
    rmdir("sdmc:/atmosphere/exefs_patches/nichole_logo");

    // Prevent this from running again.
    deleteFile("sdmc:/atmosphere/contents/010000000000DA7A/flags/boot2.flag");
    
    return 0;
}
