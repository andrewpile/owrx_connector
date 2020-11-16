#pragma once

#include "handler.hpp"
#include "ringbuffer.hpp"
#include <stdint.h>
#include <rtl-sdr.h>
#include <cstdlib>

// this should be the default according to rtl-sdr.h
#define RTL_BUFFER_SIZE 16 * 32 * 512

class RtlHandler: public Handler {
    public:
        void set_device(char* device) override;
        int open() override;
        int read() override;
        int close() override;
        int set_center_frequency(double frequency) override;
        int set_sample_rate(double sample_rate) override;
        // TODO introduce gainspec
        int set_gain() override;
        int set_ppm(int32_t ppm) override;
        int set_iqswap(bool iqswap) override;
        uint32_t get_buffer_size() override;
        void set_buffers(Ringbuffer<float>* float_buffer) override;
        void callback(unsigned char* buf, uint32_t len);
    private:
        char* device_id = "0";
        rtlsdr_dev_t* dev;
        bool iqswap;
        uint32_t rtl_buffer_size = RTL_BUFFER_SIZE;
        uint8_t* conversion_buffer = (uint8_t*) malloc(sizeof(uint8_t) * rtl_buffer_size);
        Ringbuffer<float>* float_buffer;
        uint32_t verbose_device_search(char *s);
};