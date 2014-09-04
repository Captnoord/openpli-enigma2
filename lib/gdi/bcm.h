#ifndef __lib_gdi_bcm_h
#define __lib_gdi_bcm_h

/* Broadcom proprietary ioctl command for accelerated graphic api */
#define FBIO_ACCEL  0x23


/*!
 * \note thanks for pastebin giving me the names http://pastebin.com/eFVRYbvx
 * The rest of the value's are calculated based on the binary format.
 *
 * For this description the bits per channel (bpc) are numbered from 1 to 4 but this
 * is only for readability.
 *
 * Example: BPXL_eA8_Y8_Cb8_Cr8 = 0xBE48888
 *
 * | 101111100100 | 1000 | 1000 | 1000 | 1000 |
 * |     type     |											exact meaning of type is currently unknown; I suspected it to have multiple identifiers (flags).
 *                | bpc 1|									channel 1 bit count
 *                       | bpc 2|							channel 2 bit count
 *                              | bpc 3|					channel 3 bit count
 *                                     | bpc 4|				channel 4 bit count
 */
enum BPXL_Format
{
	BPXL_eA8_Y8_Cb8_Cr8			= 0x0BE48888,
	BPXL_eCr8_Cb8_Y8_A8			= 0x0B1B8888,
	BPXL_eY8_Cb8_Cr8_A8			= 0x0B398888,
	BPXL_eA8_Cr8_Cb8_Y8			= 0x0BC68888,
	BPXL_eCr8_Y18_Cb8_Y08		= 0x0A278888,
	BPXL_eY18_Cr8_Y08_Cb8		= 0x0A728888,
	BPXL_eY08_Cb8_Y18_Cr8		= 0x0AD88888,
	BPXL_eCb8_Y08_Cr8_Y18		= 0x0A8D8888,
	BPXL_eCb8_Y18_Cr8_Y08		= 0x0A2D8888,
	BPXL_eY18_Cb8_Y08_Cr8		= 0x0A788888,
	BPXL_eY08_Cr8_Y18_Cb8		= 0x0AD28888,
	BPXL_eCr8_Y08_Cb8_Y18		= 0x0A878888,
	BPXL_eY8					= 0x0AE40800,
	BPXL_eCb8_Cr8				= 0x0AE40088,
	BPXL_eCr8_Cb8				= 0x0AE10088,
	BPXL_eX2_Cr10_Y10_Cb10		= 0x0AD22AAA,
	BPXL_eX2_Y010_Cb10_Y110_X2_Cr10_Y010_Cb10_X2_Y110_Cr10_Y010_X2_Cb10_Y110_Cr10 = 0x2AD8AAAA,
	BPXL_eCr10_Y110_Cb10_Y010	= 0x0A27AAAA,
	BPXL_eY110_Cr10_Y010_Cb10	= 0x0A72AAAA,
	BPXL_eY010_Cb10_Y110_Cr10	= 0x0AD8AAAA,
	BPXL_eCb10_Y010_Cr10_Y110	= 0x0A8DAAAA,
	BPXL_eCb10_Y110_Cr10_Y010	= 0x0A2DAAAA,
	BPXL_eY110_Cb10_Y010_Cr10	= 0x0A78AAAA,
	BPXL_eY010_Cr10_Y110_Cb10	= 0x0AD2AAAA,
	BPXL_eCr10_Y010_Cb10_Y110	= 0x0A87AAAA,
	BPXL_eA8_R8_G8_B8			= 0x07E48888, // supported.
	BPXL_eA8_B8_G8_R8			= 0x07C68888,
	BPXL_eR8_G8_B8_A8			= 0x07398888,
	BPXL_eB8_G8_R8_A8 			= 0x071B8888,
	BPXL_eX8_R8_G8_B8 			= 0x06E48888,
	BPXL_eX8_B8_G8_R8 			= 0x06C68888,
	BPXL_eR8_G8_B8_X8 			= 0x06398888,
	BPXL_eB8_G8_R8_X8 			= 0x061B8888,
	BPXL_eR8_G8_B8 				= 0x06240888,
	BPXL_eB8_G8_R8 				= 0x06060888,
	BPXL_eR5_G6_B5 				= 0x06E40565,
	BPXL_eB5_G6_R5 				= 0x06C60565,
	BPXL_eA1_R5_G5_B5 			= 0x07E41555,
	BPXL_eA1_B5_G5_R5 			= 0x07C61555,
	BPXL_eR5_G5_B5_A1 			= 0x07395551,
	BPXL_eB5_G5_R5_A1			= 0x071B5551,
	BPXL_eX1_R5_G5_B5 			= 0x06E41555,
	BPXL_eX1_B5_G5_R5 			= 0x06C61555,
	BPXL_eR5_G5_B5_X1 			= 0x06395551,
	BPXL_eB5_G5_R5_X1 			= 0x061B5551,
	BPXL_eW1_R5_G5_B5 			= 0x47E41555,
	BPXL_eW1_B5_G5_R5 			= 0x47C61555,
	BPXL_eR5_G5_B5_W1 			= 0x47395551,
	BPXL_eB5_G5_R5_W1 			= 0x471B5551,
	BPXL_eA4_R4_G4_B4 			= 0x07E44444,
	BPXL_eA4_B4_G4_R4 			= 0x07C64444,
	BPXL_eR4_G4_B4_A4 			= 0x07394444,
	BPXL_eB4_G4_R4_A4 			= 0x071B4444,
	BPXL_eX4_R4_G4_B4 			= 0x06E44444,
	BPXL_eX4_B4_G4_R4 			= 0x06C64444,
	BPXL_eR4_G4_B4_X4 			= 0x06394444,
	BPXL_eB4_G4_R4_X4 			= 0x061B4444,
	BPXL_eP1 					= 0x12E40001,
	BPXL_eP2					= 0x12E40002, // supported (possibly).
	BPXL_eP4 					= 0x12E40004,
	BPXL_eP8 					= 0x12E40008, // supported.
	BPXL_eA8_P8 				= 0x13E48008,
	BPXL_eY8_P8 				= 0x1AE40808,
	BPXL_eA1					= 0x01390001,
	BPXL_eA2 					= 0x01390002,
	BPXL_eA4 					= 0x01390004,
	BPXL_eA8 					= 0x01390008,
	BPXL_eW1 					= 0x41390001,
	BPXL_eL8 					= 0x22E40008,
	BPXL_eL8_A8 				= 0x07390088,
	BPXL_eZ16 					= 0x20000088,
	BPXL_eL4_A4 				= 0x07390044,
	BPXL_eL15_L05_A6 			= 0x07390556,
	BPXL_INVALID 				= 0x0,
};

/* Broadcom accelerated graphic instructions.
 */
enum bcm_accel
{
	SRC_ADDR					= 0x00,
	SRC_PITCH					= 0x01, // or STRIDE, comments are not very conclusive.
	SRC_WIDTH					= 0x02,
	SRC_HEIGHT					= 0x03,
	SRC_COLOR_FMT				= 0x04, // used with: BPXL_eA8_R8_G8_B8 and BPXL_eP8
	SRC_SURFACE					= 0x05, // set source surface (based on last parameters)
	UNK_06						= 0x06,
	UNK_07						= 0x07,
	UNK_08						= 0x08,
	UNK_09						= 0x09,
	UNK_0A						= 0x0A,
	UNK_0B						= 0x0B,
	UNK_0C						= 0x0C,
	UNK_0D						= 0x0D,
	UNK_0E						= 0x0E,
	UNK_0F						= 0x0F,
	UNK_10						= 0x10,
	UNK_11						= 0x11,
	UNK_12						= 0x12,
	UNK_13						= 0x13,
	UNK_14						= 0x14,
	UNK_15						= 0x15,
	UNK_16						= 0x16,
	UNK_17						= 0x17,
	UNK_18						= 0x18,
	UNK_19						= 0x19,
	UNK_1A						= 0x1A,
	UNK_1B						= 0x1B,
	UNK_1C						= 0x1C,
	UNK_1D						= 0x1D,
	UNK_1E						= 0x1E,
	UNK_1F						= 0x1F,
	UNK_20						= 0x20,
	UNK_21						= 0x21,
	UNK_22						= 0x22,
	UNK_23						= 0x23,
	UNK_24						= 0x24,
	UNK_25						= 0x25,
	UNK_26						= 0x26,
	UNK_27						= 0x27,
	UNK_28						= 0x28,
	UNK_29						= 0x29,
	UNK_2A						= 0x2A,
	UNK_2B						= 0x2B,
	UNK_2C						= 0x2C,
	SET_RECT_COLOR				= 0x2D, //! \note this name is guessed
	SET_RECT_X					= 0x2E, // prepare rect x
	SET_RECT_Y					= 0x2F, // prepare rect y
	SET_RECT_WIDTH				= 0x30, // prepare rect width
	SET_RECT_HEIGHT				= 0x31, // prepare rect height
	SET_RECT_AS_SRC				= 0x32, // set this rect as source rect
	UNK_33						= 0x33,
	UNK_34						= 0x34,
	UNK_35						= 0x35,
	UNK_36						= 0x36,
	UNK_37						= 0x37,
	UNK_38						= 0x38,
	UNK_39						= 0x39,
	UNK_3A						= 0x3A,
	UNK_3B						= 0x3B,
	UNK_3C						= 0x3C,
	UNK_3D						= 0x3D,
	UNK_3E						= 0x3E,
	UNK_3F						= 0x3F,
	UNK_40						= 0x40,
	UNK_41						= 0x41,
	UNK_42						= 0x42,
	RESET_SRC					= 0x43, // clear to reset ( reset the source )
	UNK_44						= 0x44,
	RESET_DST					= 0x45, // clear to reset ( reset the destination )
	UNK_46						= 0x46,
	UNK_47						= 0x47,
	UNK_48						= 0x48,
	UNK_49						= 0x49,
	UNK_4A						= 0x4A,
	UNK_4B						= 0x4B,
	UNK_4C						= 0x4C, // something with a color format?
	UNK_4D						= 0x4D,
	UNK_4E						= 0x4E,
	UNK_4F						= 0x4F,
	UNK_50						= 0x50,
	UNK_51						= 0x51,
	UNK_52						= 0x52,
	RESET_DST					= 0x53, // clear to reset ( reset the destination )
	UNK_54						= 0x54,
	UNK_55						= 0x55,
	UNK_56						= 0x56,
	UNK_57						= 0x57,
	UNK_58						= 0x58,
	UNK_59						= 0x59,
	UNK_5A						= 0x5A,
	RESET_PATTERN				= 0x5B, // clear to reset ( isn't this reset pattern buffer? )
	RESET_BLEND					= 0x67, // clear to reset
	SET_OUTPUT_SURFACE			= 0x69, // set output surface
	UNK_6A						= 0x6A,
	UNK_6B						= 0x6B,
	UNK_6C						= 0x6C,
	UNK_6D						= 0x6D,
	SET_RECT_AS_OUTPUT			= 0x6E, // set this rect as output rect /see SET_RECT_AS_SRC
	COLOR_KEYING_UNK1			= 0x6F, // set to 0 when used with color keying
	COLOR_KEYING_UNK2			= 0x70, // set to 0 when used with color keying
	COLOR_KEYING_UNK3			= 0x71, // set to 2 when used with color keying
	COLOR_KEYING_UNK4			= 0x72, // set to 2 when used with color keying.
	COLOR_KEYING_SELECT			= 0x73, // select color keying (blue screen?)
	UNK_74						= 0x74,
	RESET_OUTPUT				= 0x75, // reset the output, clear to reset
	EXEC_LIST					= 0x77, // clear to execute the instruction list.
	SRC_PALETTE_SIZE			= 0x78, // Set the palette size, which currently is 256 colors
	SRC_PALETTE_ADDR			= 0x79,
	SRC_PALETTE_COLOR_FMT		= 0x7A, // same as SRC_COLOR_FMT but I don't think a palette could have a palette 0x7e48888
	UNK_7B						= 0x7B,
	UNK_7C						= 0x7C,
	UNK_7D						= 0x7D,
	UNK_7E						= 0x7E,
	UNK_7F						= 0x7F,
	/*!
	 * apply blend
	 * param: blend flags:
	 * - SUPPORTED			= 0			returns non zero when alpha blending is supported (guessed).
	 * - ALPHATEST			= 1
	 * - ALPHABLEND			= 2
	 * - SCALE				= 4
	 * - KEEP_ASPECT_RATIO	= 8
	 *
	 * \todo figure out what the blend flags actually are, and how they should be used.
	 * \note these parameter enums are extracted from various places of the source code. It is by far not complete
	 */
	SET_BLEND_FLAGS				= 0x80,
};

#endif // __lib_gdi_bcm_h