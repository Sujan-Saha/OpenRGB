#include "Detector.h"
#include "AsusAuraAddressableController.h"
#include "AsusAuraMainboardController.h"
#include "AsusAuraMouseController.h"
#include "RGBController.h"
#include "RGBController_AsusAuraUSB.h"
#include "RGBController_AsusAuraMouse.h"
#include <stdexcept>
#include <hidapi/hidapi.h>

#define AURA_USB_VID                            0x0B05
#define AURA_TERMINAL_PID                       0x1889
#define AURA_ADDRESSABLE_1_PID                  0x1867
#define AURA_ADDRESSABLE_2_PID                  0x1872
#define AURA_ADDRESSABLE_3_PID                  0x18A3
#define AURA_ADDRESSABLE_4_PID                  0x18A5
#define AURA_MOTHERBOARD_1_PID                  0x18F3
#define AURA_MOTHERBOARD_2_PID                  0x1939
#define AURA_ROG_GLADIUS_II_CORE_PID            0x18DD
#define AURA_ROG_GLADIUS_II_PID                 0x1845
#define AURA_ROG_GLADIUS_II_ORIGIN_PID          0x1877

void DetectAsusAuraUSBAddressable(hid_device_info* info, const std::string& name)
{
    hid_device* dev = hid_open_path(info->path);

    if(dev)
    {
        AuraAddressableController* controller = new AuraAddressableController(dev, info->path);
        RGBController_AuraUSB* rgb_controller = new RGBController_AuraUSB(controller);
        rgb_controller->name = name;
        ResourceManager::get()->RegisterRGBController(rgb_controller);
    }
}

void DetectAsusAuraUSBMotherboards(hid_device_info* info, const std::string& name)
{
    hid_device* dev = hid_open_path(info->path);
    if(dev)
    {
        try
        {
            AuraMainboardController* controller = new AuraMainboardController(dev, info->path);
            RGBController_AuraUSB* rgb_controller = new RGBController_AuraUSB(controller);
            rgb_controller->name = name;
            ResourceManager::get()->RegisterRGBController(rgb_controller);
        }
        catch(std::runtime_error&)
        {
            // reading the config table failed
        }
    }
}

void DetectAsusAuraUSBMice(hid_device_info* info, const std::string& name)
{
    hid_device* dev = hid_open_path(info->path);
    if(dev)
    {
        AuraMouseController* controller = new AuraMouseController(dev, info->path);
        RGBController_AuraMouse* rgb_controller = new RGBController_AuraMouse(controller);
        rgb_controller->name = name;
        ResourceManager::get()->RegisterRGBController(rgb_controller);
    }
}

REGISTER_HID_DETECTOR   ("ASUS ROG AURA Terminal",     DetectAsusAuraUSBAddressable,  AURA_USB_VID, AURA_TERMINAL_PID);
REGISTER_HID_DETECTOR   ("ASUS Aura Addressable",      DetectAsusAuraUSBAddressable,  AURA_USB_VID, AURA_ADDRESSABLE_1_PID);
REGISTER_HID_DETECTOR   ("ASUS Aura Addressable",      DetectAsusAuraUSBAddressable,  AURA_USB_VID, AURA_ADDRESSABLE_2_PID);
REGISTER_HID_DETECTOR   ("ASUS Aura Addressable",      DetectAsusAuraUSBAddressable,  AURA_USB_VID, AURA_ADDRESSABLE_3_PID);
REGISTER_HID_DETECTOR   ("ASUS Aura Addressable",      DetectAsusAuraUSBAddressable,  AURA_USB_VID, AURA_ADDRESSABLE_4_PID);
REGISTER_HID_DETECTOR   ("ASUS Aura Motherboard",      DetectAsusAuraUSBMotherboards, AURA_USB_VID, AURA_MOTHERBOARD_1_PID);
REGISTER_HID_DETECTOR   ("ASUS Aura Motherboard",      DetectAsusAuraUSBMotherboards, AURA_USB_VID, AURA_MOTHERBOARD_2_PID);
REGISTER_HID_DETECTOR_IP("ASUS ROG Gladius II Core",   DetectAsusAuraUSBMice,         AURA_USB_VID, AURA_ROG_GLADIUS_II_CORE_PID,   0, 0xFF01);
REGISTER_HID_DETECTOR_IP("ASUS ROG Gladius II",        DetectAsusAuraUSBMice,         AURA_USB_VID, AURA_ROG_GLADIUS_II_PID,        2, 0xFF01);
REGISTER_HID_DETECTOR_IP("ASUS ROG Gladius II Origin", DetectAsusAuraUSBMice,         AURA_USB_VID, AURA_ROG_GLADIUS_II_ORIGIN_PID, 2, 0xFF01);
