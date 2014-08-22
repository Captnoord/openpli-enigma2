/*
  Interface to the Dreambox dm800/dm8000 proprietary accel interface.
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

#define FBIO_ACCEL  0x23

static unsigned int displaylist[1024];
static int ptr;
static bool supportblendingflags = true;

#define P(x, y) do { displaylist[ptr++] = x; displaylist[ptr++] = y; } while (0)
#define C(x) P(x, 0)

static int fb_fd = -1;
static int exec_list(void);

int bcm_accel_init(void)
{
	fb_fd = open("/dev/fb0", O_RDWR);
	if (fb_fd < 0)
	{
		perror("/dev/fb0");
		return 1;
	}
	if (exec_list())
	{
		fprintf(stderr, "BCM accel interface not available - %m\n");
		close(fb_fd);
		fb_fd = -1;
		return 1;
	}
	/* now test for blending flags support */
	P(0x80, 0);
	if (exec_list())
	{
		supportblendingflags = false;
	}
#ifdef FORCE_NO_BLENDING_ACCELERATION
	/* hardware doesn't allow us to detect whether the opcode is working */
	supportblendingflags = false;
#endif
	return 0;
}

void bcm_accel_close(void)
{
	if (fb_fd >= 0)
	{
		close(fb_fd);
		fb_fd = -1;
	}
}

static int exec_list(void)
{
	int ret;
	struct
	{
		void *ptr;
		int len;
	} l;

	l.ptr = displaylist;
	l.len = ptr;
	ret = ioctl(fb_fd, FBIO_ACCEL, &l);
	ptr = 0;
	return ret;
}

bool bcm_accel_has_alphablending()
{
	return supportblendingflags;
}

enum bcm_color_format
{
	ARGB8888		= 0x07e48888,
	INDEXED_8BPP	= 0x12e40008
};

/* instruction pipeline documentations... or at least a bit... */
enum bcm_accel
{
	SRC_ADDR				= 0x00,
	SRC_PITCH				= 0x01, // or STRIDE...
	SRC_WIDTH				= 0x02,
	SRC_HEIGHT				= 0x03,
	SRC_COLOR_FMT			= 0x04, // ARGB 8888 = 0x7e48888, indexed palette 8bit  = 0x12e40008
	SRC_SURFACE				= 0x05, // set source surface (based on last parameters)
	UNK_06					= 0x06,
	UNK_07					= 0x07,
	UNK_08					= 0x08,
	UNK_09					= 0x09,
	UNK_0A					= 0x0A,
	UNK_0B					= 0x0B,
	UNK_0C					= 0x0C,
	UNK_0D					= 0x0D,
	UNK_0E					= 0x0E,
	UNK_0F					= 0x0F,
	UNK_10					= 0x10,
	UNK_11					= 0x11,
	UNK_12					= 0x12,
	UNK_13					= 0x13,
	UNK_14					= 0x14,
	UNK_15					= 0x15,
	UNK_16					= 0x16,
	UNK_17					= 0x17,
	UNK_18					= 0x18,
	UNK_19					= 0x19,
	UNK_1A					= 0x1A,
	UNK_1B					= 0x1B,
	UNK_1C					= 0x1C,
	UNK_1D					= 0x1D,
	UNK_1E					= 0x1E,
	UNK_1F					= 0x1F,
	UNK_20					= 0x20,
	UNK_21					= 0x21,
	UNK_22					= 0x22,
	UNK_23					= 0x23,
	UNK_24					= 0x24,
	UNK_25					= 0x25,
	UNK_26					= 0x26,
	UNK_27					= 0x27,
	UNK_28					= 0x28,
	UNK_29					= 0x29,
	UNK_2A					= 0x2A,
	UNK_2B					= 0x2B,
	UNK_2C					= 0x2C,
	SET_RECT_COLOR			= 0x2D, /* \note this name is guessed */
	SET_RECT_X				= 0x2E, // P(0x2e, dst_x); // prepare output rect
	SET_RECT_Y				= 0x2F, // P(0x2f, dst_y);
	SET_RECT_WIDTH			= 0x30, // P(0x30, dwidth);
	SET_RECT_HEIGHT			= 0x31, // P(0x31, dheight);
	SET_RECT_AS_SRC			= 0x32, // C(0x32); // set this rect as source rect
	UNK_33					= 0x33,
	UNK_34					= 0x34,
	UNK_35					= 0x35,
	UNK_36					= 0x36,
	UNK_37					= 0x37,
	UNK_38					= 0x38,
	UNK_39					= 0x39,
	UNK_3A					= 0x3A,
	UNK_3B					= 0x3B,
	UNK_3C					= 0x3C,
	UNK_3D					= 0x3D,
	UNK_3E					= 0x3E,
	UNK_3F					= 0x3F,
	UNK_40					= 0x40,
	UNK_41					= 0x41,
	UNK_42					= 0x42,
	RESET_SRC				= 0x43, // clear to reset ( reset the source )
	UNK_44					= 0x44,
	RESET_DST				= 0x45, // clear to reset ( reset the destination )
	UNK_46					= 0x46,
	UNK_47					= 0x47,
	UNK_48					= 0x48,
	UNK_49					= 0x49,
	UNK_4A					= 0x4A,
	UNK_4B					= 0x4B,
	UNK_4C					= 0x4C,
	UNK_4D					= 0x4D,
	UNK_4E					= 0x4E,
	UNK_4F					= 0x4F,
	UNK_50					= 0x50,
	UNK_51					= 0x51,
	UNK_52					= 0x52,
	RESET_DST				= 0x53, // clear to reset ( reset the destination )
	UNK_54					= 0x54,
	UNK_55					= 0x55,
	UNK_56					= 0x56,
	UNK_57					= 0x57,
	UNK_58					= 0x58,
	UNK_59					= 0x59,
	UNK_5A					= 0x5A,
	RESET_PATTERN			= 0x5B, // clear to reset ( isn't this reset pattern buffer? )
	RESET_BLEND				= 0x67, // clear to reset
	SET_OUTPUT_SURFACE		= 0x69, // set output surface
	UNK_6A					= 0x6A,
	UNK_6B					= 0x6B,
	UNK_6C					= 0x6C,
	UNK_6D					= 0x6D,
	SET_RECT_AS_OUTPUT		= 0x6E, // C(0x6e); // set this rect as output rect
	COLOR_KEYING_UNK1		= 0x6F, // P(0x6F, 0);
	COLOR_KEYING_UNK2		= 0x70, // P(0x70, 0);
	COLOR_KEYING_UNK3		= 0x71, // P(0x71, 2);
	COLOR_KEYING_UNK4		= 0x72, // P(0x72, 2);
	COLOR_KEYING_SELECT		= 0x73, // C(0x73); // select color keying (blue screen?)
	UNK_74					= 0x74,
	RESET_OUTPUT			= 0x75, // reset the output, clear to reset
	EXEC_LIST				= 0x77, // clear to execute the instruction list.
	SRC_PALETTE_SIZE		= 0x78, // our current implementation has 256 colors
	SRC_PALETTE_ADDR		= 0x79,
	SRC_PALETTE_COLOR_FMT	= 0x7A, // same as SRC_COLOR_FMT but I don't think a palette could have a palette 0x7e48888
	UNK_7B					= 0x7B,
	UNK_7C					= 0x7C,
	UNK_7D					= 0x7D,
	UNK_7E					= 0x7E,
	UNK_7F					= 0x7F,
	/*!
	 * apply blend
	 * param: blend flags:
	 * - ALPHATEST = 1
	 * - ALPHABLEND = 2
	 * - SCALE = 4
	 * - KEEP_ASPECT_RATIO = 8
	 * \todo figure out what the blend flags actually are.
	 */
	SET_BLEND_FLAGS			= 0x80,
};

void bcm_accel_blit(
		int src_addr, int src_width, int src_height, int src_stride, int src_format,
		int dst_addr, int dst_width, int dst_height, int dst_stride,
		int src_x, int src_y, int width, int height,
		int dst_x, int dst_y, int dwidth, int dheight,
		int pal_addr, int flags)
{
	C(0x43); // reset source
	C(0x53); // reset dest
	C(0x5b);  // reset pattern
	C(0x67); // reset blend
	C(0x75); // reset output

	P(0x0, src_addr); // set source addr
	P(0x1, src_stride);  // set source pitch
	P(0x2, src_width); // source width
	P(0x3, src_height); // height
	switch (src_format)
	{
	case 0:
		P(0x4, 0x7e48888); // format: ARGB 8888
		break;
	case 1:
		P(0x4, 0x12e40008); // indexed 8bit
		P(0x78, 256);
		P(0x79, pal_addr);
		P(0x7a, 0x7e48888);
		break;
	}

	C(0x5); // set source surface (based on last parameters)

	P(0x2e, src_x); // define  rect
	P(0x2f, src_y);
	P(0x30, width);
	P(0x31, height);

	C(0x32); // set this rect as source rect

	P(0x0, dst_addr); // prepare output surface
	P(0x1, dst_stride);
	P(0x2, dst_width);
	P(0x3, dst_height);
	P(0x4, 0x7e48888);

	C(0x69); // set output surface

	P(0x2e, dst_x); // prepare output rect
	P(0x2f, dst_y);
	P(0x30, dwidth);
	P(0x31, dheight);

	C(0x6e); // set this rect as output rect

	if (supportblendingflags && flags) P(0x80, flags); /* blend flags... We'd really like some blending support in the drivers, to avoid punching holes in the osd */

	C(0x77);  // do it

	exec_list();
}

void bcm_accel_fill(
		int dst_addr, int dst_width, int dst_height, int dst_stride,
		int x, int y, int width, int height,
		unsigned long color)
{
	C(0x43); // reset source
	C(0x53); // reset dest
	C(0x5b); // reset pattern
	C(0x67); // reset blend
	C(0x75); // reset output

	// clear dest surface
	P(0x0, 0);
	P(0x1, 0);
	P(0x2, 0);
	P(0x3, 0);
	P(0x4, 0);
	C(0x45);

	// clear src surface
	P(0x0, 0);
	P(0x1, 0);
	P(0x2, 0);
	P(0x3, 0);
	P(0x4, 0);
	C(0x5);

	P(0x2d, color);

	P(0x2e, x); // prepare output rect
	P(0x2f, y);
	P(0x30, width);
	P(0x31, height);
	C(0x6e); // set this rect as output rect

	P(0x0, dst_addr); // prepare output surface
	P(0x1, dst_stride);
	P(0x2, dst_width);
	P(0x3, dst_height);
	P(0x4, 0x7e48888);
	C(0x69); // set output surface

	P(0x6f, 0);
	P(0x70, 0);
	P(0x71, 2);
	P(0x72, 2);
	C(0x73); // select color keying

	C(0x77);  // do it

	exec_list();
}

