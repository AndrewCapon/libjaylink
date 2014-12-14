/*
 * This file is part of the libjaylink project.
 *
 * Copyright (C) 2014 Marc Schink <jaylink-dev@marcschink.de>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LIBJAYLINK_LIBJAYLINK_H
#define LIBJAYLINK_LIBJAYLINK_H

#include <stdlib.h>
#include <stdint.h>

/**
 * @file
 *
 * Public libjaylink header file to be used by applications.
 */

/** Error codes returned by libjaylink functions. */
enum jaylink_error {
	/** No error. */
	JAYLINK_OK = 0,
	/** Unspecific error. */
	JAYLINK_ERR = -1,
	/** Memory allocation error. */
	JAYLINK_ERR_MALLOC = -2,
	/** Invalid argument. */
	JAYLINK_ERR_ARG = -3,
	/** Timeout occurred. */
	JAYLINK_ERR_TIMEOUT = -4
};

/** libjaylink log levels. */
enum jaylink_log_level {
	/** Output no messages. */
	JAYLINK_LOG_LEVEL_NONE = 0,
	/** Output error messages. */
	JAYLINK_LOG_LEVEL_ERROR = 1,
	/** Output warnings. */
	JAYLINK_LOG_LEVEL_WARNING = 2,
	/** Output informational messages. */
	JAYLINK_LOG_LEVEL_INFO = 3,
	/** Output debug messages. */
	JAYLINK_LOG_LEVEL_DEBUG = 4
};

/**
 * USB addresses.
 *
 * The USB address is a way to identify USB devices and is related to the USB
 * Product ID (PID) of a device.
 */
enum jaylink_usb_address {
	/** USB address 0 (Product ID 0x0101). */
	JAYLINK_USB_ADDRESS_0 = 0,
	/** USB address 1 (Product ID 0x0102). */
	JAYLINK_USB_ADDRESS_1 = 1,
	/** USB address 2 (Product ID 0x0103). */
	JAYLINK_USB_ADDRESS_2 = 2,
	/** USB address 3 (Product ID 0x0104). */
	JAYLINK_USB_ADDRESS_3 = 3
};

/** Device capabilities. */
enum jaylink_device_capability {
	/** Device supports retrieval of the hardware version. */
	JAYLINK_DEV_CAP_GET_HW_VERSION = 1,
	/** Device supports adaptive clocking. */
	JAYLINK_DEV_CAP_ADAPTIVE_CLOCKING = 3,
	/** Device supports reading configuration data. */
	JAYLINK_DEV_CAP_READ_CONFIG = 4,
	/** Device supports writing configuration data. */
	JAYLINK_DEV_CAP_WRITE_CONFIG = 5,
	/** Device supports retrieval of free memory size. */
	JAYLINK_DEV_CAP_GET_FREE_MEMORY = 11,
	/** Device supports the setting of the target power supply. */
	JAYLINK_DEV_CAP_SET_TARGET_POWER = 13,
	/** Device supports target interface selection. */
	JAYLINK_DEV_CAP_SELECT_TIF = 17,
	/** Device supports retrieval of extended capabilities. */
	JAYLINK_DEV_CAP_GET_EXT_CAPS = 31
};

/** Device hardware types. */
enum jaylink_hardware_type {
	/** J-Link BASE. */
	JAYLINK_HW_TYPE_BASE = 0
};

/** Target interfaces. */
enum jaylink_target_interface {
	/** Joint Test Action Group, IEEE 1149.1 (JTAG). */
	JAYLINK_TIF_JTAG = 0,
	/** Serial Wire Debug (SWD). */
	JAYLINK_TIF_SWD = 1,
	/** Background Debug Mode 3 (BDM3). */
	JAYLINK_TIF_BDM3 = 2,
	/** Renesas’ single-wire debug interface (FINE). */
	JAYLINK_TIF_FINE = 3,
	/** 2-wire JTAG for PIC32 compliant devices. */
	JAYLINK_TIF_2W_JTAG_PIC32 = 4,

	/** <i>Helper which must be always the last element</i>. */
	__JAYLINK_TIF_MAX
};

/** Maximum valid target interface number. */
#define JAYLINK_TIF_MAX (__JAYLINK_TIF_MAX - 1)

/**
 * JTAG command versions.
 *
 * The JTAG command version only affects the device and the communication
 * protocol. The behaviour of a JTAG operation is not affected at all.
 */
enum jaylink_jtag_version {
	/**
	 * JTAG command version 2.
	 *
	 * This version is obsolete for major hardware version 5 and above. Use
	 * #JAYLINK_JTAG_V3 for these versions instead.
	 */
	JAYLINK_JTAG_V2 = 1,
	/** JTAG command version 3. */
	JAYLINK_JTAG_V3 = 2
};

/** Device hardware version. */
struct jaylink_hardware_version {
	/**
	 * Hardware type.
	 *
	 * See #jaylink_hardware_type for a description of the hardware types.
	 */
	uint8_t type;
	/** Major version. */
	uint8_t major;
	/** Minor version. */
	uint8_t minor;
	/** Revision number. */
	uint8_t revision;
};

/** Device hardware status. */
struct jaylink_hardware_status {
	/** Target reference voltage in mV. */
	uint16_t target_voltage;
	/** TCK pin state. */
	uint8_t tck;
	/** TDI pin state. */
	uint8_t tdi;
	/** TDO pin state. */
	uint8_t tdo;
	/** TMS pin state. */
	uint8_t tms;
	/** TRES pin state. */
	uint8_t tres;
	/** TRST pin state. */
	uint8_t trst;
};

/** Target interface speed value for adaptive clocking. */
#define JAYLINK_SPEED_ADAPTIVE_CLOCKING 0xffff

/** Size of the device configuration data in bytes. */
#define JAYLINK_DEV_CONFIG_SIZE		256

/** Number of bytes required to store device capabilities. */
#define JAYLINK_DEV_CAPS_SIZE		4

/** Number of bytes required to store extended device capabilities. */
#define JAYLINK_DEV_EXT_CAPS_SIZE	32

/**
 * @struct jaylink_context
 *
 * Opaque structure representing a libjaylink context.
 */
struct jaylink_context;

/**
 * @struct jaylink_device
 *
 * Opaque structure representing a device.
 */
struct jaylink_device;

/**
 * @struct jaylink_device_handle
 *
 * Opaque structure representing a handle of a device.
 */
struct jaylink_device_handle;

int jaylink_init(struct jaylink_context **ctx);
void jaylink_exit(struct jaylink_context *ctx);

const char *jaylink_strerror(int error_code);
const char *jaylink_strerror_name(int error_code);

int jaylink_log_set_level(struct jaylink_context *ctx, int level);
int jaylink_log_get_level(const struct jaylink_context *ctx);

ssize_t jaylink_get_device_list(struct jaylink_context *ctx,
		struct jaylink_device ***devices);

void jaylink_free_device_list(struct jaylink_device **devices,
		int unref_devices);

int jaylink_device_get_serial_number(const struct jaylink_device *dev,
		uint32_t *serial_number);

int jaylink_device_get_usb_address(const struct jaylink_device *dev);

struct jaylink_device *jaylink_ref_device(struct jaylink_device *dev);
void jaylink_unref_device(struct jaylink_device *dev);

int jaylink_open(struct jaylink_device *dev,
		struct jaylink_device_handle **devh);

void jaylink_close(struct jaylink_device_handle *devh);

int jaylink_get_firmware_version(struct jaylink_device_handle *devh,
		char **version);

int jaylink_get_hardware_version(struct jaylink_device_handle *devh,
		struct jaylink_hardware_version *version);

int jaylink_get_hardware_status(struct jaylink_device_handle *devh,
		struct jaylink_hardware_status *status);

int jaylink_get_caps(struct jaylink_device_handle *devh, uint8_t *caps);
int jaylink_get_extended_caps(struct jaylink_device_handle *devh,
		uint8_t *caps);

int jaylink_get_free_memory(struct jaylink_device_handle *devh, uint32_t *size);

int jaylink_set_speed(struct jaylink_device_handle *devh, uint16_t speed);

int jaylink_select_interface(struct jaylink_device_handle *devh,
		uint8_t interface);
int jaylink_get_available_interfaces(struct jaylink_device_handle *devh,
		uint32_t *interfaces);
int jaylink_get_selected_interface(struct jaylink_device_handle *devh);

int jaylink_clear_reset(struct jaylink_device_handle *devh);
int jaylink_set_reset(struct jaylink_device_handle *devh);

int jaylink_set_target_power(struct jaylink_device_handle *devh, int enable);

int jaylink_read_raw_config(struct jaylink_device_handle *devh,
		uint8_t *config);
int jaylink_write_raw_config(struct jaylink_device_handle *devh,
		const uint8_t *config);

int jaylink_jtag_io(struct jaylink_device_handle *devh, const uint8_t *tms,
		const uint8_t *tdi, uint8_t *tdo, uint16_t length, int version);
int jaylink_jtag_clear_trst(struct jaylink_device_handle *devh);
int jaylink_jtag_set_trst(struct jaylink_device_handle *devh);

int jaylink_swd_io(struct jaylink_device_handle *devh,
		const uint8_t *direction, const uint8_t *out, uint8_t *in,
		uint16_t length);

int jaylink_has_cap(const uint8_t *caps, uint32_t cap);

#endif /* LIBJAYLINK_LIBJAYLINK_H */
