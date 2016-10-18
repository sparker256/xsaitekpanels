#ifndef _READINIFILE_H_
#define _READINIFILE_H_

namespace xsaitekpanels {
    enum {
        I2R_END_ARG,
        I2R_CMD_ARG,
        I2R_INT_ARG,
        I2R_DOUBLE_ARG,
        I2R_DR_ARG
    };

    void ini2remap(const char *remap_name, ...);
}

#endif /* _READINIFILE_H_ */
