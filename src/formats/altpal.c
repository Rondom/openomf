#include <stdlib.h>
#include <string.h>

#include "formats/internal/reader.h"
#include "formats/internal/writer.h"
#include "formats/error.h"
#include "formats/palette.h"
#include "formats/altpal.h"

int sd_altpal_create(sd_altpal_file *ap) {
    if(ap == NULL) {
        return SD_INVALID_INPUT;
    }
    memset(ap, 0, sizeof(sd_altpal_file));
    return SD_SUCCESS;
}

int sd_altpals_load(sd_altpal_file *ap, const char *filename) {
    sd_reader *r = sd_reader_open(filename);
    if(!r) {
        return SD_FILE_OPEN_ERROR;
    }

    for(uint8_t i = 0; i < SD_ALTPALS_PALETTES; i++) {
        sd_palette_create(&ap->palettes[i]);
        sd_palette_load_range(r, &ap->palettes[i], 0, 256);
    }

    // Close & return
    sd_reader_close(r);
    return SD_SUCCESS;
}

int sd_altpals_save(sd_altpal_file *ap, const char *filename) {
    sd_writer *w = sd_writer_open(filename);
    if(!w) {
        return SD_FILE_OPEN_ERROR;
    }

    for(uint8_t i = 0; i < SD_ALTPALS_PALETTES; i++) {
        sd_palette_save_range(w, &ap->palettes[i], 0, 256);
    }

    // All done.
    sd_writer_close(w);
    return SD_SUCCESS;
}

void sd_altpal_free(sd_altpal_file *ap) {
}

