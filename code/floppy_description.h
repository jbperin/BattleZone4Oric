//
// Floppy layout generated by FloppyBuilder 1.3
//

#ifdef ASSEMBLER
//
// Information for the Assembler
//
#ifdef LOADER
FileStartSector .byt 135,140,143,6
FileStartTrack .byt 0,3,3,4
FileSizeLow .byt <35281,<760,<8191,<1536
FileSizeHigh .byt >35281,>760,>8191,>1536
#undef LOADER
#endif // LOADER
#undef ASSEMBLER
#else
//
// Information for the Compiler
//
#endif

//
// Summary for this floppy building session:
//
#define FLOPPY_SIDE_NUMBER 2    // Number of sides
#define FLOPPY_TRACK_NUMBER 42    // Number of tracks
#define FLOPPY_SECTOR_PER_TRACK 17   // Number of sectors per track

#define FLOPPY_LOADER_TRACK 0   // Track where the loader is stored
#define FLOPPY_LOADER_SECTOR 4   // Sector where the loader is stored
#define FLOPPY_LOADER_ADDRESS 64768   // Address where the loader is loaded on boot ($fd00)

//
// List of files written to the floppy
//
// Entry #0 '..\build\files\BattleZone.o'
// - Starts on  track 0 sector 7 and is 56 sectors long (14330 compressed bytes: 40% of 35281 bytes).
// Entry #1 '..\build\files\Font6x8.hir'
// - Starts on  track 3 sector 12 and is 3 sectors long (556 compressed bytes: 73% of 760 bytes).
// Entry #2 '..\data\hrscreen.bin'
// - Starts on  track 3 sector 15 and is 8 sectors long (1860 compressed bytes: 22% of 8191 bytes).
// Entry #3 'Reserved sectors'
// - Starts on  track 4 sector 6 and is 6 sectors long (1536 bytes).
//
// 79 sectors used, out of 1428. (5% of the total disk size used)
//
#define LOADER_SECTOR_BUFFER $200
#define LOADER_BASE_ZERO_PAGE $F2
#define LOADER_GAME_PROGRAM 0
#define LOADER_GAME_PROGRAM_ADDRESS $400
#define LOADER_GAME_PROGRAM_TRACK 0
#define LOADER_GAME_PROGRAM_SECTOR 135
#define LOADER_GAME_PROGRAM_SIZE 35281
#define LOADER_GAME_PROGRAM_SIZE_COMPRESSED 14330
#define LOADER_FONT_6x8 1
#define HIRES_SCREEN 2

//
// Metadata
//
#ifdef METADATA_STORAGE

#endif // METADATA_STORAGE

