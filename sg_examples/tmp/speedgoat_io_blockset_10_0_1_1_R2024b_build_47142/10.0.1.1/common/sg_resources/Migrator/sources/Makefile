export PATH := $(QNX_HOST)/usr/bin;$(PATH)

usb: usb.img

usb.img:
	mkxfs -t qnx6fsimg root.build partition.img
	diskimage -o usb.img -c usb.cfg -b ipl-diskpc1
	rm partition.img

