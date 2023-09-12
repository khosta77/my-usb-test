#include <iostream>
#include <cassert>
#include <cstdio>

#include <libusb-1.0/libusb.h>


int main() {
    libusb_context *context = NULL;
    libusb_device **list = NULL;
    int rc = 0;
    ssize_t count = 0;

    rc = libusb_init(&context);
    assert(rc == 0);

    count = libusb_get_device_list(context, &list);
  //  assert(count > 0);

    printf("Total USB devices found: %zd\n", count);

    for (size_t idx = 0; idx < count; ++idx) {
        libusb_device *device = list[idx];
        libusb_device_descriptor desc = {0};

        rc = libusb_get_device_descriptor(device, &desc);
        assert(rc == 0);

        printf("Vendor:Device = %04x:%04x\n", desc.idVendor, desc.idProduct);
    }

    libusb_free_device_list(list, count);
    libusb_exit(context);
#if 0
    [[maybe_unused]] struct usb_bus *bus;
    [[maybe_unused]] struct usb_device *dev;

    libusb_init(NULL);
#endif
    return 0;
}
// https://twinpeppers.blogspot.com/2014/07/usb-2.html
#define DEV_VID 0x1D34
#define DEV_PID 0x0004
#define DEV_CONFIG 1
#define DEV_INTF 0
#define EP_IN 0x81

unsigned char COMMAND_1[8] = {0x1F,0x1E,0x92,0x7C,0xB8,0x1,0x14,0x03};
unsigned char COMMAND_2[8] = {0x00,0x1E,0x92,0x7C,0xB8,0x1,0x14,0x04};
unsigned char COMMAND_ON[8] = {0x00,0x00,0x00,0x00,0x0,0x1,0x14,0x05};

int main(int argc, char * argv[]) {
    libusb_init(NULL);
    libusb_set_debug(NULL, 3);
    handle = libusb_open_device_with_vid_pid(NULL, DEV_VID, DEV_PID);

    if (libusb_kernel_driver_active(handle,DEV_INTF))
        libusb_detach_kernel_driver(handle, DEV_INTF);
    
    if ((ret = libusb_set_configuration(handle, DEV_CONFIG)) < 0) {
        printf("Ошибка конфигурации\n");
    }

    if (libusb_claim_interface(handle, DEV_INTF) < 0) {
        printf("Ошибка интерфейса\n");
    }
    ret = libusb_control_transfer(handle, LIBUSB_REQUEST_TYPE_CLASS|LIBUSB_RECIPIENT_INTERFACE|LIBUSB_ENDPOINT_OUT, 0x9, 0x200, 0, COMMAND_1, 8, 100);
    libusb_interrupt_transfer(handle, EP_IN, buf, 8, &ret, 100);
    ret = libusb_control_transfer(handle, LIBUSB_REQUEST_TYPE_CLASS|LIBUSB_RECIPIENT_INTERFACE|LIBUSB_ENDPOINT_OUT, 0x9, 0x200, 0, COMMAND_2, 8, 100);
    libusb_interrupt_transfer(handle, EP_IN, buf, 8, &ret, 100);
    COMMAND_ON[0] = r;
    COMMAND_ON[1] = g;
    COMMAND_ON[2] = b;
    ret = libusb_control_transfer(handle, LIBUSB_REQUEST_TYPE_CLASS|LIBUSB_RECIPIENT_INTERFACE|LIBUSB_ENDPOINT_OUT, 0x9, 0x200, 0, COMMAND_ON, 8, 100);
    buf[7] = 0;
    libusb_interrupt_transfer(handle, EP_IN, buf, 8, &ret, 100);
    if (buf[7] != 1) {
        printf("Сбой в управлении устройством\n");
    }

    libusb_attach_kernel_driver(handle, DEV_INTF);
    libusb_close(handle);
    libusb_exit(NULL);
    return 0;
}

