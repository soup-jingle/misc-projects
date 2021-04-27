	###
	#	Patrick Bunetic
	# CS312: Project 3
	# 800441093
	###

# Offset extractor
.data

STR_MESSAGE1: .asciiz "Enter a valid segmented-virtual memory address (0 - 33554431): "
STR_MESSAGE2: .asciiz "\n"
STR_MESSAGE3: .asciiz "Segment:              "
STR_MESSAGE4: .asciiz "Entered Address:      "
STR_MESSAGE5: .asciiz "Offset Address:       "
STR_MESSAGE6: .asciiz "The entered address exceeds 33554431. Enter a valid address.\n"
STR_MESSAGE7: .asciiz "The entered address is a negative address. Enter a valid address.\n"
	# /Offset extractor

	########################################################
	# ORIGINAL DATA START:
	#
	#
	#########################################################
NEWLINE:	 .asciiz "\n"
SEG_FAULT:	.asciiz "Segmentation fault!\n"
SEG_BASE:	 .asciiz "\nSegmentation Base:    "
SEG_LIMIT:	.asciiz "\nSegment Limit:        "
VIRT_PAGE_NO:	.asciiz "\n\nVirtual Page Number:  "
VIRT_OFF:	.asciiz "\nOffset (in VM):       "
PHYS_PAGE:	.asciiz "\n\nPhysical Page:        "
PHYS_ADDR:	.asciiz "\nPhysical Address:     "
	########################################################
	# ORIGINAL DATA END:
	#
	#
	#########################################################
	
.text
.globl main

# Segment Table
SEG_TABLE:	
	#####	<Base>		<Limit>
	.word	0,				4193999		# for segment 0
	.word	4194000,	2304561		# for segment 1
	.word	6498562,	189652		# for segment 2
	.word	6688215,	3964511		# for segment 3
	.word	10652727,	876901		# for segment 4
	.word	11529629,	1009452		# for segment 5
	.word	12539082,	4193999		# for segment 6
	.word	16733082,	1823003		# for segment 7
	##### end SEG_TABLE #########################################

# VMT
VMT:
	# .word <Physical Page #>, <Valid Flag>
	.word	8,	0		#virtual page 0
	.word	97,	0		# virtual page 1
	.word	118,	0		# virtual page 2
	.word	14,	0		# virtual page 3
	.word	47,	0		# virtual page 4
	.word	64,	0		# virtual page 5
	.word	33,	0		# virtual page 6
	.word	117,	0		# virtual page 7
	.word	127,	0		# virtual page 8
	.word	126,	0		# virtual page 9
	.word	31,	0		# virtual page 10
	.word	15,	0		# virtual page 11
	.word	48,	0		# virtual page 12
	.word	44,	0		# virtual page 13
	.word	16,	0		# virtual page 14
	.word	17,	0		# virtual page 15
	.word	116,	0		# virtual page 16
	.word	72,	0		# virtual page 17
	.word	69,	0		# virtual page 18
	.word	16,	0		# virtual page 19
	.word	89,	0		# virtual page 20
	.word	52,	0		# virtual page 21
	.word	109,	0		# virtual page 22
	.word	21,	0		# virtual page 23
	.word	19,	0		# virtual page 24
	.word	103,	0		# virtual page 25
	.word	113,	0		# virtual page 26
	.word	115,	0		# virtual page 27
	.word	124,	0		# virtual page 28
	.word	99,	0		# virtual page 29
	.word	28,	0		# virtual page 30
	.word	88,	0		# virtual page 31
	.word	89,	0		# virtual page 32
	.word	102,	0		# virtual page 33
	.word	127,	0		# virtual page 34
	.word	35,	0		# virtual page 35
	.word	95,	0		# virtual page 36
	.word	101,	0		# virtual page 37
	.word	20,	0		# virtual page 38
	.word	117,	0		# virtual page 39
	.word	118,	0		# virtual page 40
	.word	54,	0		# virtual page 41
	.word	33,	0		# virtual page 42
	.word	11,	0		# virtual page 43
	.word	60,	0		# virtual page 44
	.word	13,	0		# virtual page 45
	.word	95,	0		# virtual page 46
	.word	75,	0		# virtual page 47
	.word	77,	0		# virtual page 48
	.word	41,	0		# virtual page 49
	.word	92,	0		# virtual page 50
	.word	28,	0		# virtual page 51
	.word	66,	0		# virtual page 52
	.word	79,	0		# virtual page 53
	.word	30,	0		# virtual page 54
	.word	123,	0		# virtual page 55
	.word	119,	0		# virtual page 56
	.word	120,	0		# virtual page 57
	.word	9,	0		# virtual page 58
	.word	76,	0		# virtual page 59
	.word	18,	0		# virtual page 60
	.word	71,	0		# virtual page 61
	.word	3,	0		# virtual page 62
	.word	109,	0		# virtual page 63
	.word	64,	0		# virtual page 64
	.word	61,	0		# virtual page 65
	.word	85,	0		# virtual page 66
	.word	17,	0		# virtual page 67
	.word	66,	0		# virtual page 68
	.word	48,	0		# virtual page 69
	.word	84,	0		# virtual page 70
	.word	76,	0		# virtual page 71
	.word	41,	0		# virtual page 72
	.word	121,	0		# virtual page 73
	.word	66,	0		# virtual page 74
	.word	106,	0		# virtual page 75
	.word	93,	0		# virtual page 76
	.word	110,	0		# virtual page 77
	.word	111,	0		# virtual page 78
	.word	5,	0		# virtual page 79
	.word	100,	0		# virtual page 80
	.word	16,	0		# virtual page 81
	.word	35,	0		# virtual page 82
	.word	87,	0		# virtual page 83
	.word	97,	0		# virtual page 84
	.word	5,	0		# virtual page 85
	.word	64,	0		# virtual page 86
	.word	76,	0		# virtual page 87
	.word	91,	0		# virtual page 88
	.word	72,	0		# virtual page 89
	.word	36,	0		# virtual page 90
	.word	91,	0		# virtual page 91
	.word	64,	0		# virtual page 92
	.word	31,	0		# virtual page 93
	.word	77,	0		# virtual page 94
	.word	23,	0		# virtual page 95
	.word	42,	0		# virtual page 96
	.word	77,	0		# virtual page 97
	.word	64,	0		# virtual page 98
	.word	1,	0		# virtual page 99
	.word	96,	0		# virtual page 100
	.word	9,	0		# virtual page 101
	.word	43,	0		# virtual page 102
	.word	33,	0		# virtual page 103
	.word	32,	0		# virtual page 104
	.word	48,	0		# virtual page 105
	.word	73,	0		# virtual page 106
	.word	85,	0		# virtual page 107
	.word	28,	0		# virtual page 108
	.word	55,	0		# virtual page 109
	.word	6,	0		# virtual page 110
	.word	104,	0		# virtual page 111
	.word	66,	0		# virtual page 112
	.word	99,	0		# virtual page 113
	.word	100,	0		# virtual page 114
	.word	102,	0		# virtual page 115
	.word	64,	0		# virtual page 116
	.word	60,	0		# virtual page 117
	.word	29,	0		# virtual page 118
	.word	47,	0		# virtual page 119
	.word	72,	0		# virtual page 120
	.word	63,	0		# virtual page 121
	.word	10,	0		# virtual page 122
	.word	75,	0		# virtual page 123
	.word	16,	0		# virtual page 124
	.word	83,	0		# virtual page 125
	.word	67,	0		# virtual page 126
	.word	125,	0		# virtual page 127
	.word	30,	0		# virtual page 128
	.word	126,	0		# virtual page 129
	.word	8,	0		# virtual page 130
	.word	27,	0		# virtual page 131
	.word	66,	0		# virtual page 132
	.word	89,	0		# virtual page 133
	.word	95,	0		# virtual page 134
	.word	28,	0		# virtual page 135
	.word	100,	0		# virtual page 136
	.word	65,	0		# virtual page 137
	.word	127,	0		# virtual page 138
	.word	115,	0		# virtual page 139
	.word	127,	0		# virtual page 140
	.word	80,	0		# virtual page 141
	.word	109,	0		# virtual page 142
	.word	28,	0		# virtual page 143
	.word	110,	0		# virtual page 144
	.word	11,	0		# virtual page 145
	.word	101,	0		# virtual page 146
	.word	116,	0		# virtual page 147
	.word	103,	0		# virtual page 148
	.word	93,	0		# virtual page 149
	.word	123,	0		# virtual page 150
	.word	77,	0		# virtual page 151
	.word	69,	0		# virtual page 152
	.word	69,	0		# virtual page 153
	.word	2,	0		# virtual page 154
	.word	66,	0		# virtual page 155
	.word	10,	0		# virtual page 156
	.word	75,	0		# virtual page 157
	.word	45,	0		# virtual page 158
	.word	72,	0		# virtual page 159
	.word	36,	0		# virtual page 160
	.word	56,	0		# virtual page 161
	.word	116,	0		# virtual page 162
	.word	6,	0		# virtual page 163
	.word	111,	0		# virtual page 164
	.word	6,	0		# virtual page 165
	.word	57,	0		# virtual page 166
	.word	103,	0		# virtual page 167
	.word	124,	0		# virtual page 168
	.word	22,	0		# virtual page 169
	.word	44,	0		# virtual page 170
	.word	109,	0		# virtual page 171
	.word	17,	0		# virtual page 172
	.word	33,	0		# virtual page 173
	.word	108,	0		# virtual page 174
	.word	72,	0		# virtual page 175
	.word	112,	0		# virtual page 176
	.word	113,	0		# virtual page 177
	.word	111,	0		# virtual page 178
	.word	39,	0		# virtual page 179
	.word	92,	0		# virtual page 180
	.word	81,	0		# virtual page 181
	.word	35,	0		# virtual page 182
	.word	78,	0		# virtual page 183
	.word	90,	0		# virtual page 184
	.word	66,	0		# virtual page 185
	.word	85,	0		# virtual page 186
	.word	104,	0		# virtual page 187
	.word	53,	0		# virtual page 188
	.word	111,	0		# virtual page 189
	.word	83,	0		# virtual page 190
	.word	31,	0		# virtual page 191
	.word	68,	0		# virtual page 192
	.word	99,	0		# virtual page 193
	.word	77,	0		# virtual page 194
	.word	107,	0		# virtual page 195
	.word	111,	0		# virtual page 196
	.word	122,	0		# virtual page 197
	.word	1,	0		# virtual page 198
	.word	39,	0		# virtual page 199
	.word	112,	0		# virtual page 200
	.word	21,	0		# virtual page 201
	.word	24,	0		# virtual page 202
	.word	106,	0		# virtual page 203
	.word	87,	0		# virtual page 204
	.word	18,	0		# virtual page 205
	.word	74,	0		# virtual page 206
	.word	20,	0		# virtual page 207
	.word	81,	0		# virtual page 208
	.word	124,	0		# virtual page 209
	.word	73,	0		# virtual page 210
	.word	39,	0		# virtual page 211
	.word	41,	0		# virtual page 212
	.word	126,	0		# virtual page 213
	.word	93,	0		# virtual page 214
	.word	89,	0		# virtual page 215
	.word	15,	0		# virtual page 216
	.word	30,	0		# virtual page 217
	.word	75,	0		# virtual page 218
	.word	103,	0		# virtual page 219
	.word	25,	0		# virtual page 220
	.word	40,	0		# virtual page 221
	.word	124,	0		# virtual page 222
	.word	43,	0		# virtual page 223
	.word	7,	0		# virtual page 224
	.word	103,	0		# virtual page 225
	.word	91,	0		# virtual page 226
	.word	113,	0		# virtual page 227
	.word	75,	0		# virtual page 228
	.word	27,	0		# virtual page 229
	.word	127,	0		# virtual page 230
	.word	7,	0		# virtual page 231
	.word	73,	0		# virtual page 232
	.word	40,	0		# virtual page 233
	.word	10,	0		# virtual page 234
	.word	19,	0		# virtual page 235
	.word	91,	0		# virtual page 236
	.word	12,	0		# virtual page 237
	.word	81,	0		# virtual page 238
	.word	41,	0		# virtual page 239
	.word	24,	0		# virtual page 240
	.word	19,	0		# virtual page 241
	.word	61,	0		# virtual page 242
	.word	29,	0		# virtual page 243
	.word	86,	0		# virtual page 244
	.word	78,	0		# virtual page 245
	.word	113,	0		# virtual page 246
	.word	22,	0		# virtual page 247
	.word	109,	0		# virtual page 248
	.word	65,	0		# virtual page 249
	.word	44,	0		# virtual page 250
	.word	100,	0		# virtual page 251
	.word	62,	0		# virtual page 252
	.word	92,	0		# virtual page 253
	.word	113,	0		# virtual page 254
	.word	20,	0		# virtual page 255
	.word	116,	0		# virtual page 256
	.word	45,	0		# virtual page 257
	.word	102,	0		# virtual page 258
	.word	65,	0		# virtual page 259
	.word	10,	0		# virtual page 260
	.word	83,	0		# virtual page 261
	.word	123,	0		# virtual page 262
	.word	45,	0		# virtual page 263
	.word	14,	0		# virtual page 264
	.word	54,	0		# virtual page 265
	.word	75,	0		# virtual page 266
	.word	16,	0		# virtual page 267
	.word	36,	0		# virtual page 268
	.word	117,	0		# virtual page 269
	.word	71,	0		# virtual page 270
	.word	47,	0		# virtual page 271
	.word	77,	0		# virtual page 272
	.word	32,	0		# virtual page 273
	.word	17,	0		# virtual page 274
	.word	49,	0		# virtual page 275
	.word	105,	0		# virtual page 276
	.word	40,	0		# virtual page 277
	.word	38,	0		# virtual page 278
	.word	46,	0		# virtual page 279
	.word	123,	0		# virtual page 280
	.word	19,	0		# virtual page 281
	.word	64,	0		# virtual page 282
	.word	10,	0		# virtual page 283
	.word	45,	0		# virtual page 284
	.word	116,	0		# virtual page 285
	.word	123,	0		# virtual page 286
	.word	1,	0		# virtual page 287
	.word	20,	0		# virtual page 288
	.word	27,	0		# virtual page 289
	.word	54,	0		# virtual page 290
	.word	2,	0		# virtual page 291
	.word	52,	0		# virtual page 292
	.word	9,	0		# virtual page 293
	.word	60,	0		# virtual page 294
	.word	65,	0		# virtual page 295
	.word	71,	0		# virtual page 296
	.word	39,	0		# virtual page 297
	.word	36,	0		# virtual page 298
	.word	8,	0		# virtual page 299
	.word	58,	0		# virtual page 300
	.word	55,	0		# virtual page 301
	.word	117,	0		# virtual page 302
	.word	77,	0		# virtual page 303
	.word	121,	0		# virtual page 304
	.word	10,	0		# virtual page 305
	.word	14,	0		# virtual page 306
	.word	10,	0		# virtual page 307
	.word	108,	0		# virtual page 308
	.word	115,	0		# virtual page 309
	.word	69,	0		# virtual page 310
	.word	73,	0		# virtual page 311
	.word	65,	0		# virtual page 312
	.word	125,	0		# virtual page 313
	.word	79,	0		# virtual page 314
	.word	126,	0		# virtual page 315
	.word	109,	0		# virtual page 316
	.word	89,	0		# virtual page 317
	.word	96,	0		# virtual page 318
	.word	26,	0		# virtual page 319
	.word	109,	0		# virtual page 320
	.word	26,	0		# virtual page 321
	.word	18,	0		# virtual page 322
	.word	93,	0		# virtual page 323
	.word	82,	0		# virtual page 324
	.word	37,	0		# virtual page 325
	.word	11,	0		# virtual page 326
	.word	108,	0		# virtual page 327
	.word	124,	0		# virtual page 328
	.word	98,	0		# virtual page 329
	.word	90,	0		# virtual page 330
	.word	35,	0		# virtual page 331
	.word	38,	0		# virtual page 332
	.word	56,	0		# virtual page 333
	.word	35,	0		# virtual page 334
	.word	44,	0		# virtual page 335
	.word	35,	0		# virtual page 336
	.word	57,	0		# virtual page 337
	.word	124,	0		# virtual page 338
	.word	81,	0		# virtual page 339
	.word	102,	0		# virtual page 340
	.word	25,	0		# virtual page 341
	.word	22,	0		# virtual page 342
	.word	14,	0		# virtual page 343
	.word	72,	0		# virtual page 344
	.word	101,	0		# virtual page 345
	.word	32,	0		# virtual page 346
	.word	107,	0		# virtual page 347
	.word	6,	0		# virtual page 348
	.word	113,	0		# virtual page 349
	.word	104,	0		# virtual page 350
	.word	9,	0		# virtual page 351
	.word	9,	0		# virtual page 352
	.word	19,	0		# virtual page 353
	.word	68,	0		# virtual page 354
	.word	122,	0		# virtual page 355
	.word	107,	0		# virtual page 356
	.word	14,	0		# virtual page 357
	.word	48,	0		# virtual page 358
	.word	85,	0		# virtual page 359
	.word	54,	0		# virtual page 360
	.word	81,	0		# virtual page 361
	.word	56,	0		# virtual page 362
	.word	10,	0		# virtual page 363
	.word	111,	0		# virtual page 364
	.word	98,	0		# virtual page 365
	.word	25,	0		# virtual page 366
	.word	116,	0		# virtual page 367
	.word	83,	0		# virtual page 368
	.word	21,	0		# virtual page 369
	.word	35,	0		# virtual page 370
	.word	45,	0		# virtual page 371
	.word	96,	0		# virtual page 372
	.word	1,	0		# virtual page 373
	.word	97,	0		# virtual page 374
	.word	38,	0		# virtual page 375
	.word	23,	0		# virtual page 376
	.word	52,	0		# virtual page 377
	.word	124,	0		# virtual page 378
	.word	119,	0		# virtual page 379
	.word	1,	0		# virtual page 380
	.word	38,	0		# virtual page 381
	.word	93,	0		# virtual page 382
	.word	115,	0		# virtual page 383
	.word	112,	0		# virtual page 384
	.word	108,	0		# virtual page 385
	.word	18,	0		# virtual page 386
	.word	0,	0		# virtual page 387
	.word	7,	0		# virtual page 388
	.word	46,	0		# virtual page 389
	.word	115,	0		# virtual page 390
	.word	38,	0		# virtual page 391
	.word	124,	0		# virtual page 392
	.word	91,	0		# virtual page 393
	.word	5,	0		# virtual page 394
	.word	101,	0		# virtual page 395
	.word	29,	0		# virtual page 396
	.word	27,	0		# virtual page 397
	.word	30,	0		# virtual page 398
	.word	76,	0		# virtual page 399
	.word	17,	0		# virtual page 400
	.word	6,	0		# virtual page 401
	.word	74,	0		# virtual page 402
	.word	71,	0		# virtual page 403
	.word	97,	0		# virtual page 404
	.word	19,	0		# virtual page 405
	.word	110,	0		# virtual page 406
	.word	57,	0		# virtual page 407
	.word	55,	0		# virtual page 408
	.word	83,	0		# virtual page 409
	.word	43,	0		# virtual page 410
	.word	74,	0		# virtual page 411
	.word	101,	0		# virtual page 412
	.word	95,	0		# virtual page 413
	.word	5,	0		# virtual page 414
	.word	3,	0		# virtual page 415
	.word	40,	0		# virtual page 416
	.word	15,	0		# virtual page 417
	.word	69,	0		# virtual page 418
	.word	24,	0		# virtual page 419
	.word	46,	0		# virtual page 420
	.word	108,	0		# virtual page 421
	.word	27,	0		# virtual page 422
	.word	4,	0		# virtual page 423
	.word	87,	0		# virtual page 424
	.word	104,	0		# virtual page 425
	.word	8,	0		# virtual page 426
	.word	91,	0		# virtual page 427
	.word	57,	0		# virtual page 428
	.word	77,	0		# virtual page 429
	.word	123,	0		# virtual page 430
	.word	92,	0		# virtual page 431
	.word	102,	0		# virtual page 432
	.word	116,	0		# virtual page 433
	.word	59,	0		# virtual page 434
	.word	70,	0		# virtual page 435
	.word	113,	0		# virtual page 436
	.word	55,	0		# virtual page 437
	.word	4,	0		# virtual page 438
	.word	110,	0		# virtual page 439
	.word	46,	0		# virtual page 440
	.word	40,	0		# virtual page 441
	.word	117,	0		# virtual page 442
	.word	13,	0		# virtual page 443
	.word	58,	0		# virtual page 444
	.word	4,	0		# virtual page 445
	.word	42,	0		# virtual page 446
	.word	94,	0		# virtual page 447
	.word	59,	0		# virtual page 448
	.word	98,	0		# virtual page 449
	.word	37,	0		# virtual page 450
	.word	105,	0		# virtual page 451
	.word	105,	0		# virtual page 452
	.word	48,	0		# virtual page 453
	.word	114,	0		# virtual page 454
	.word	25,	0		# virtual page 455
	.word	78,	0		# virtual page 456
	.word	96,	0		# virtual page 457
	.word	10,	0		# virtual page 458
	.word	21,	0		# virtual page 459
	.word	73,	0		# virtual page 460
	.word	95,	0		# virtual page 461
	.word	121,	0		# virtual page 462
	.word	77,	0		# virtual page 463
	.word	89,	0		# virtual page 464
	.word	71,	0		# virtual page 465
	.word	60,	0		# virtual page 466
	.word	83,	0		# virtual page 467
	.word	24,	0		# virtual page 468
	.word	85,	0		# virtual page 469
	.word	109,	0		# virtual page 470
	.word	109,	0		# virtual page 471
	.word	6,	0		# virtual page 472
	.word	29,	0		# virtual page 473
	.word	34,	0		# virtual page 474
	.word	104,	0		# virtual page 475
	.word	8,	0		# virtual page 476
	.word	124,	0		# virtual page 477
	.word	18,	0		# virtual page 478
	.word	47,	0		# virtual page 479
	.word	49,	0		# virtual page 480
	.word	79,	0		# virtual page 481
	.word	121,	0		# virtual page 482
	.word	28,	0		# virtual page 483
	.word	63,	0		# virtual page 484
	.word	98,	0		# virtual page 485
	.word	62,	0		# virtual page 486
	.word	13,	0		# virtual page 487
	.word	105,	0		# virtual page 488
	.word	44,	0		# virtual page 489
	.word	83,	0		# virtual page 490
	.word	59,	0		# virtual page 491
	.word	88,	0		# virtual page 492
	.word	57,	0		# virtual page 493
	.word	94,	0		# virtual page 494
	.word	71,	0		# virtual page 495
	.word	115,	0		# virtual page 496
	.word	103,	0		# virtual page 497
	.word	22,	0		# virtual page 498
	.word	22,	0		# virtual page 499
	.word	95,	0		# virtual page 500
	.word	85,	0		# virtual page 501
	.word	111,	0		# virtual page 502
	.word	95,	0		# virtual page 503
	.word	70,	0		# virtual page 504
	.word	25,	0		# virtual page 505
	.word	121,	0		# virtual page 506
	.word	2,	0		# virtual page 507
	.word	88,	0		# virtual page 508
	.word	49,	0		# virtual page 509
	.word	5,	0		# virtual page 510
	.word	28,	0		# virtual page 511
	.word	16,	0		# virtual page 512
	.word	60,	0		# virtual page 513
	.word	11,	0		# virtual page 514
	.word	88,	0		# virtual page 515
	.word	57,	0		# virtual page 516
	.word	107,	0		# virtual page 517
	.word	72,	0		# virtual page 518
	.word	8,	0		# virtual page 519
	.word	48,	0		# virtual page 520
	.word	50,	0		# virtual page 521
	.word	43,	0		# virtual page 522
	.word	116,	0		# virtual page 523
	.word	107,	0		# virtual page 524
	.word	67,	0		# virtual page 525
	.word	114,	0		# virtual page 526
	.word	113,	0		# virtual page 527
	.word	58,	0		# virtual page 528
	.word	60,	0		# virtual page 529
	.word	17,	0		# virtual page 530
	.word	54,	0		# virtual page 531
	.word	77,	0		# virtual page 532
	.word	31,	0		# virtual page 533
	.word	83,	0		# virtual page 534
	.word	108,	0		# virtual page 535
	.word	119,	0		# virtual page 536
	.word	4,	0		# virtual page 537
	.word	67,	0		# virtual page 538
	.word	4,	0		# virtual page 539
	.word	49,	0		# virtual page 540
	.word	10,	0		# virtual page 541
	.word	77,	0		# virtual page 542
	.word	77,	0		# virtual page 543
	.word	98,	0		# virtual page 544
	.word	19,	0		# virtual page 545
	.word	33,	0		# virtual page 546
	.word	70,	0		# virtual page 547
	.word	94,	0		# virtual page 548
	.word	49,	0		# virtual page 549
	.word	88,	0		# virtual page 550
	.word	49,	0		# virtual page 551
	.word	44,	0		# virtual page 552
	.word	91,	0		# virtual page 553
	.word	90,	0		# virtual page 554
	.word	104,	0		# virtual page 555
	.word	12,	0		# virtual page 556
	.word	101,	0		# virtual page 557
	.word	127,	0		# virtual page 558
	.word	116,	0		# virtual page 559
	.word	56,	0		# virtual page 560
	.word	47,	0		# virtual page 561
	.word	116,	0		# virtual page 562
	.word	92,	0		# virtual page 563
	.word	107,	0		# virtual page 564
	.word	28,	0		# virtual page 565
	.word	97,	0		# virtual page 566
	.word	59,	0		# virtual page 567
	.word	32,	0		# virtual page 568
	.word	69,	0		# virtual page 569
	.word	72,	0		# virtual page 570
	.word	21,	0		# virtual page 571
	.word	28,	0		# virtual page 572
	.word	111,	0		# virtual page 573
	.word	49,	0		# virtual page 574
	.word	107,	0		# virtual page 575
	.word	46,	0		# virtual page 576
	.word	59,	0		# virtual page 577
	.word	4,	0		# virtual page 578
	.word	13,	0		# virtual page 579
	.word	54,	0		# virtual page 580
	.word	29,	0		# virtual page 581
	.word	54,	0		# virtual page 582
	.word	48,	0		# virtual page 583
	.word	100,	0		# virtual page 584
	.word	15,	0		# virtual page 585
	.word	39,	0		# virtual page 586
	.word	64,	0		# virtual page 587
	.word	66,	0		# virtual page 588
	.word	7,	0		# virtual page 589
	.word	75,	0		# virtual page 590
	.word	120,	0		# virtual page 591
	.word	117,	0		# virtual page 592
	.word	38,	0		# virtual page 593
	.word	9,	0		# virtual page 594
	.word	47,	0		# virtual page 595
	.word	64,	0		# virtual page 596
	.word	50,	0		# virtual page 597
	.word	96,	0		# virtual page 598
	.word	117,	0		# virtual page 599
	.word	73,	0		# virtual page 600
	.word	70,	0		# virtual page 601
	.word	80,	0		# virtual page 602
	.word	94,	0		# virtual page 603
	.word	32,	0		# virtual page 604
	.word	72,	0		# virtual page 605
	.word	120,	0		# virtual page 606
	.word	30,	0		# virtual page 607
	.word	125,	0		# virtual page 608
	.word	28,	0		# virtual page 609
	.word	124,	0		# virtual page 610
	.word	86,	0		# virtual page 611
	.word	73,	0		# virtual page 612
	.word	23,	0		# virtual page 613
	.word	41,	0		# virtual page 614
	.word	46,	0		# virtual page 615
	.word	96,	0		# virtual page 616
	.word	55,	0		# virtual page 617
	.word	92,	0		# virtual page 618
	.word	36,	0		# virtual page 619
	.word	22,	0		# virtual page 620
	.word	17,	0		# virtual page 621
	.word	31,	0		# virtual page 622
	.word	36,	0		# virtual page 623
	.word	120,	0		# virtual page 624
	.word	10,	0		# virtual page 625
	.word	22,	0		# virtual page 626
	.word	88,	0		# virtual page 627
	.word	84,	0		# virtual page 628
	.word	74,	0		# virtual page 629
	.word	26,	0		# virtual page 630
	.word	65,	0		# virtual page 631
	.word	123,	0		# virtual page 632
	.word	110,	0		# virtual page 633
	.word	35,	0		# virtual page 634
	.word	7,	0		# virtual page 635
	.word	69,	0		# virtual page 636
	.word	125,	0		# virtual page 637
	.word	107,	0		# virtual page 638
	.word	13,	0		# virtual page 639
	.word	86,	0		# virtual page 640
	.word	30,	0		# virtual page 641
	.word	80,	0		# virtual page 642
	.word	73,	0		# virtual page 643
	.word	32,	0		# virtual page 644
	.word	8,	0		# virtual page 645
	.word	122,	0		# virtual page 646
	.word	83,	0		# virtual page 647
	.word	41,	0		# virtual page 648
	.word	57,	0		# virtual page 649
	.word	63,	0		# virtual page 650
	.word	59,	0		# virtual page 651
	.word	14,	0		# virtual page 652
	.word	107,	0		# virtual page 653
	.word	67,	0		# virtual page 654
	.word	32,	0		# virtual page 655
	.word	73,	0		# virtual page 656
	.word	68,	0		# virtual page 657
	.word	100,	0		# virtual page 658
	.word	126,	0		# virtual page 659
	.word	47,	0		# virtual page 660
	.word	77,	0		# virtual page 661
	.word	85,	0		# virtual page 662
	.word	72,	0		# virtual page 663
	.word	60,	0		# virtual page 664
	.word	37,	0		# virtual page 665
	.word	8,	0		# virtual page 666
	.word	55,	0		# virtual page 667
	.word	19,	0		# virtual page 668
	.word	119,	0		# virtual page 669
	.word	82,	0		# virtual page 670
	.word	97,	0		# virtual page 671
	.word	65,	0		# virtual page 672
	.word	41,	0		# virtual page 673
	.word	74,	0		# virtual page 674
	.word	13,	0		# virtual page 675
	.word	66,	0		# virtual page 676
	.word	86,	0		# virtual page 677
	.word	114,	0		# virtual page 678
	.word	70,	0		# virtual page 679
	.word	70,	0		# virtual page 680
	.word	127,	0		# virtual page 681
	.word	25,	0		# virtual page 682
	.word	46,	0		# virtual page 683
	.word	53,	0		# virtual page 684
	.word	125,	0		# virtual page 685
	.word	127,	0		# virtual page 686
	.word	21,	0		# virtual page 687
	.word	112,	0		# virtual page 688
	.word	58,	0		# virtual page 689
	.word	59,	0		# virtual page 690
	.word	74,	0		# virtual page 691
	.word	90,	0		# virtual page 692
	.word	33,	0		# virtual page 693
	.word	90,	0		# virtual page 694
	.word	49,	0		# virtual page 695
	.word	23,	0		# virtual page 696
	.word	83,	0		# virtual page 697
	.word	73,	0		# virtual page 698
	.word	22,	0		# virtual page 699
	.word	19,	0		# virtual page 700
	.word	28,	0		# virtual page 701
	.word	117,	0		# virtual page 702
	.word	65,	0		# virtual page 703
	.word	70,	0		# virtual page 704
	.word	37,	0		# virtual page 705
	.word	48,	0		# virtual page 706
	.word	75,	0		# virtual page 707
	.word	55,	0		# virtual page 708
	.word	107,	0		# virtual page 709
	.word	87,	0		# virtual page 710
	.word	48,	0		# virtual page 711
	.word	63,	0		# virtual page 712
	.word	111,	0		# virtual page 713
	.word	49,	0		# virtual page 714
	.word	36,	0		# virtual page 715
	.word	16,	0		# virtual page 716
	.word	48,	0		# virtual page 717
	.word	27,	0		# virtual page 718
	.word	43,	0		# virtual page 719
	.word	117,	0		# virtual page 720
	.word	86,	0		# virtual page 721
	.word	98,	0		# virtual page 722
	.word	100,	0		# virtual page 723
	.word	92,	0		# virtual page 724
	.word	48,	0		# virtual page 725
	.word	113,	0		# virtual page 726
	.word	37,	0		# virtual page 727
	.word	17,	0		# virtual page 728
	.word	96,	0		# virtual page 729
	.word	44,	0		# virtual page 730
	.word	77,	0		# virtual page 731
	.word	76,	0		# virtual page 732
	.word	85,	0		# virtual page 733
	.word	27,	0		# virtual page 734
	.word	86,	0		# virtual page 735
	.word	110,	0		# virtual page 736
	.word	122,	0		# virtual page 737
	.word	75,	0		# virtual page 738
	.word	42,	0		# virtual page 739
	.word	8,	0		# virtual page 740
	.word	45,	0		# virtual page 741
	.word	113,	0		# virtual page 742
	.word	56,	0		# virtual page 743
	.word	29,	0		# virtual page 744
	.word	115,	0		# virtual page 745
	.word	81,	0		# virtual page 746
	.word	70,	0		# virtual page 747
	.word	41,	0		# virtual page 748
	.word	106,	0		# virtual page 749
	.word	94,	0		# virtual page 750
	.word	9,	0		# virtual page 751
	.word	97,	0		# virtual page 752
	.word	127,	0		# virtual page 753
	.word	35,	0		# virtual page 754
	.word	115,	0		# virtual page 755
	.word	61,	0		# virtual page 756
	.word	96,	0		# virtual page 757
	.word	97,	0		# virtual page 758
	.word	76,	0		# virtual page 759
	.word	52,	0		# virtual page 760
	.word	53,	0		# virtual page 761
	.word	122,	0		# virtual page 762
	.word	4,	0		# virtual page 763
	.word	70,	0		# virtual page 764
	.word	11,	0		# virtual page 765
	.word	13,	0		# virtual page 766
	.word	72,	0		# virtual page 767
	.word	64,	0		# virtual page 768
	.word	16,	0		# virtual page 769
	.word	99,	0		# virtual page 770
	.word	83,	0		# virtual page 771
	.word	60,	0		# virtual page 772
	.word	6,	0		# virtual page 773
	.word	10,	0		# virtual page 774
	.word	7,	0		# virtual page 775
	.word	103,	0		# virtual page 776
	.word	114,	0		# virtual page 777
	.word	63,	0		# virtual page 778
	.word	60,	0		# virtual page 779
	.word	7,	0		# virtual page 780
	.word	20,	0		# virtual page 781
	.word	18,	0		# virtual page 782
	.word	88,	0		# virtual page 783
	.word	60,	0		# virtual page 784
	.word	28,	0		# virtual page 785
	.word	68,	0		# virtual page 786
	.word	31,	0		# virtual page 787
	.word	5,	0		# virtual page 788
	.word	27,	0		# virtual page 789
	.word	116,	0		# virtual page 790
	.word	77,	0		# virtual page 791
	.word	7,	0		# virtual page 792
	.word	56,	0		# virtual page 793
	.word	122,	0		# virtual page 794
	.word	98,	0		# virtual page 795
	.word	10,	0		# virtual page 796
	.word	36,	0		# virtual page 797
	.word	20,	0		# virtual page 798
	.word	62,	0		# virtual page 799
	.word	69,	0		# virtual page 800
	.word	80,	0		# virtual page 801
	.word	64,	0		# virtual page 802
	.word	109,	0		# virtual page 803
	.word	91,	0		# virtual page 804
	.word	93,	0		# virtual page 805
	.word	104,	0		# virtual page 806
	.word	68,	0		# virtual page 807
	.word	37,	0		# virtual page 808
	.word	84,	0		# virtual page 809
	.word	68,	0		# virtual page 810
	.word	45,	0		# virtual page 811
	.word	50,	0		# virtual page 812
	.word	23,	0		# virtual page 813
	.word	125,	0		# virtual page 814
	.word	63,	0		# virtual page 815
	.word	12,	0		# virtual page 816
	.word	23,	0		# virtual page 817
	.word	14,	0		# virtual page 818
	.word	18,	0		# virtual page 819
	.word	61,	0		# virtual page 820
	.word	72,	0		# virtual page 821
	.word	112,	0		# virtual page 822
	.word	81,	0		# virtual page 823
	.word	18,	0		# virtual page 824
	.word	82,	0		# virtual page 825
	.word	118,	0		# virtual page 826
	.word	16,	0		# virtual page 827
	.word	31,	0		# virtual page 828
	.word	10,	0		# virtual page 829
	.word	118,	0		# virtual page 830
	.word	96,	0		# virtual page 831
	.word	3,	0		# virtual page 832
	.word	32,	0		# virtual page 833
	.word	41,	0		# virtual page 834
	.word	33,	0		# virtual page 835
	.word	110,	0		# virtual page 836
	.word	25,	0		# virtual page 837
	.word	84,	0		# virtual page 838
	.word	24,	0		# virtual page 839
	.word	96,	0		# virtual page 840
	.word	0,	0		# virtual page 841
	.word	40,	0		# virtual page 842
	.word	66,	0		# virtual page 843
	.word	51,	0		# virtual page 844
	.word	89,	0		# virtual page 845
	.word	103,	0		# virtual page 846
	.word	103,	0		# virtual page 847
	.word	91,	0		# virtual page 848
	.word	87,	0		# virtual page 849
	.word	73,	0		# virtual page 850
	.word	113,	0		# virtual page 851
	.word	109,	0		# virtual page 852
	.word	79,	0		# virtual page 853
	.word	30,	0		# virtual page 854
	.word	127,	0		# virtual page 855
	.word	94,	0		# virtual page 856
	.word	107,	0		# virtual page 857
	.word	52,	0		# virtual page 858
	.word	54,	0		# virtual page 859
	.word	13,	0		# virtual page 860
	.word	35,	0		# virtual page 861
	.word	123,	0		# virtual page 862
	.word	87,	0		# virtual page 863
	.word	4,	0		# virtual page 864
	.word	105,	0		# virtual page 865
	.word	103,	0		# virtual page 866
	.word	23,	0		# virtual page 867
	.word	123,	0		# virtual page 868
	.word	36,	0		# virtual page 869
	.word	22,	0		# virtual page 870
	.word	43,	0		# virtual page 871
	.word	30,	0		# virtual page 872
	.word	96,	0		# virtual page 873
	.word	51,	0		# virtual page 874
	.word	34,	0		# virtual page 875
	.word	17,	0		# virtual page 876
	.word	68,	0		# virtual page 877
	.word	26,	0		# virtual page 878
	.word	119,	0		# virtual page 879
	.word	48,	0		# virtual page 880
	.word	68,	0		# virtual page 881
	.word	61,	0		# virtual page 882
	.word	103,	0		# virtual page 883
	.word	27,	0		# virtual page 884
	.word	24,	0		# virtual page 885
	.word	70,	0		# virtual page 886
	.word	0,	0		# virtual page 887
	.word	114,	0		# virtual page 888
	.word	108,	0		# virtual page 889
	.word	126,	0		# virtual page 890
	.word	123,	0		# virtual page 891
	.word	93,	0		# virtual page 892
	.word	89,	0		# virtual page 893
	.word	109,	0		# virtual page 894
	.word	75,	0		# virtual page 895
	.word	80,	0		# virtual page 896
	.word	20,	0		# virtual page 897
	.word	67,	0		# virtual page 898
	.word	118,	0		# virtual page 899
	.word	13,	0		# virtual page 900
	.word	101,	0		# virtual page 901
	.word	118,	0		# virtual page 902
	.word	36,	0		# virtual page 903
	.word	106,	0		# virtual page 904
	.word	91,	0		# virtual page 905
	.word	45,	0		# virtual page 906
	.word	117,	0		# virtual page 907
	.word	84,	0		# virtual page 908
	.word	63,	0		# virtual page 909
	.word	93,	0		# virtual page 910
	.word	24,	0		# virtual page 911
	.word	20,	0		# virtual page 912
	.word	70,	0		# virtual page 913
	.word	49,	0		# virtual page 914
	.word	26,	0		# virtual page 915
	.word	81,	0		# virtual page 916
	.word	10,	0		# virtual page 917
	.word	48,	0		# virtual page 918
	.word	123,	0		# virtual page 919
	.word	86,	0		# virtual page 920
	.word	59,	0		# virtual page 921
	.word	26,	0		# virtual page 922
	.word	7,	0		# virtual page 923
	.word	22,	0		# virtual page 924
	.word	18,	0		# virtual page 925
	.word	18,	0		# virtual page 926
	.word	99,	0		# virtual page 927
	.word	109,	0		# virtual page 928
	.word	7,	0		# virtual page 929
	.word	2,	0		# virtual page 930
	.word	103,	0		# virtual page 931
	.word	41,	0		# virtual page 932
	.word	68,	0		# virtual page 933
	.word	60,	0		# virtual page 934
	.word	43,	0		# virtual page 935
	.word	73,	0		# virtual page 936
	.word	89,	0		# virtual page 937
	.word	93,	0		# virtual page 938
	.word	101,	0		# virtual page 939
	.word	5,	0		# virtual page 940
	.word	49,	0		# virtual page 941
	.word	119,	0		# virtual page 942
	.word	114,	0		# virtual page 943
	.word	14,	0		# virtual page 944
	.word	69,	0		# virtual page 945
	.word	111,	0		# virtual page 946
	.word	50,	0		# virtual page 947
	.word	22,	0		# virtual page 948
	.word	15,	0		# virtual page 949
	.word	35,	0		# virtual page 950
	.word	25,	0		# virtual page 951
	.word	19,	0		# virtual page 952
	.word	66,	0		# virtual page 953
	.word	80,	0		# virtual page 954
	.word	3,	0		# virtual page 955
	.word	64,	0		# virtual page 956
	.word	56,	0		# virtual page 957
	.word	52,	0		# virtual page 958
	.word	72,	0		# virtual page 959
	.word	101,	0		# virtual page 960
	.word	44,	0		# virtual page 961
	.word	111,	0		# virtual page 962
	.word	17,	0		# virtual page 963
	.word	89,	0		# virtual page 964
	.word	41,	0		# virtual page 965
	.word	47,	0		# virtual page 966
	.word	106,	0		# virtual page 967
	.word	69,	0		# virtual page 968
	.word	66,	0		# virtual page 969
	.word	12,	0		# virtual page 970
	.word	24,	0		# virtual page 971
	.word	42,	0		# virtual page 972
	.word	4,	0		# virtual page 973
	.word	49,	0		# virtual page 974
	.word	44,	0		# virtual page 975
	.word	38,	0		# virtual page 976
	.word	41,	0		# virtual page 977
	.word	61,	0		# virtual page 978
	.word	88,	0		# virtual page 979
	.word	115,	0		# virtual page 980
	.word	14,	0		# virtual page 981
	.word	105,	0		# virtual page 982
	.word	2,	0		# virtual page 983
	.word	48,	0		# virtual page 984
	.word	104,	0		# virtual page 985
	.word	106,	0		# virtual page 986
	.word	23,	0		# virtual page 987
	.word	100,	0		# virtual page 988
	.word	50,	0		# virtual page 989
	.word	25,	0		# virtual page 990
	.word	34,	0		# virtual page 991
	.word	64,	0		# virtual page 992
	.word	106,	0		# virtual page 993
	.word	81,	0		# virtual page 994
	.word	29,	0		# virtual page 995
	.word	36,	0		# virtual page 996
	.word	124,	0		# virtual page 997
	.word	24,	0		# virtual page 998
	.word	6,	0		# virtual page 999
	.word	101,	0		# virtual page 1000
	.word	127,	0		# virtual page 1001
	.word	2,	0		# virtual page 1002
	.word	54,	0		# virtual page 1003
	.word	78,	0		# virtual page 1004
	.word	31,	0		# virtual page 1005
	.word	83,	0		# virtual page 1006
	.word	111,	0		# virtual page 1007
	.word	100,	0		# virtual page 1008
	.word	90,	0		# virtual page 1009
	.word	100,	0		# virtual page 1010
	.word	52,	0		# virtual page 1011
	.word	110,	0		# virtual page 1012
	.word	112,	0		# virtual page 1013
	.word	72,	0		# virtual page 1014
	.word	93,	0		# virtual page 1015
	.word	53,	0		# virtual page 1016
	.word	20,	0		# virtual page 1017
	.word	46,	0		# virtual page 1018
	.word	106,	0		# virtual page 1019
	.word	9,	0		# virtual page 1020
	.word	104,	0		# virtual page 1021
	.word	9,	0		# virtual page 1022
	.word	24,	0		# virtual page 1023
	##### end VMT ###################################################

# Table Search
TABLE_FOR_SEARCH:
	# .word <first number>, <second number>
	.word	00000000,	0999999		# row #0
	.word	11111111,	1000000		# row #1
	.word	22222222,	2111111		# row #2
	.word	33333333,	3222222		# row #3
	.word	44444444,	4333333		# row #4
	.word	55555555,	5444444		# row #5
	.word	66666666,	6555555		# row #6
	.word	77777777,	7666666		# row #7
	.word	88888888,	8777777		# row #8
	.word	99999999,	9888888		# row #9
	##### end TABLE_FOR_SEARCH ######################################

	# ############################################################### #
# Segment_Number_Offset_Extractor.ASM                             #
#                                                                 #
# This program extracts the segment number and the offset address #
# from a segmented-virtual-memory address.                        #
#                                                                 #
# Assumptions:                                                    #
#     (1) 32MB virtual memory space                               #
#     (2) 4MB Physical memory space                               #
#     (3) Page size is 32KB                                       #
#     (4) 8 segments (the entire virtual memory space is split to #
#         8 segements)                                            #
#                                                                 #
# Based on the above assumptions, the possible address values are #
# in the range of 0 through 33554431, in which the first 3 bits   #
# are for the segment number, while the rest (25-3 = 22) of the   #
# 22 bits are for the offset address. Thus, the max. size of each #
# segment is 2^22 bits = 4MB.                                     #
#                                                                 #
# At the end of theprogram:                                       #
#    (a) $s2 registers holds the segment number                   #
#    (b) $s3 regsiter holds the offset address in the segment     #
#                                                                 #
# Date: 2:30 PM, September 9, 2015                                #
# ############################################################### #   

main:   la $s2, 0		# initialize $s2 register by 0
	la $s3, 0		# initialize $s3 register by 0
	li $s4, 33554431	# max. valid address

	# Prompt a segmented-virtual-memory address (0 - 33554431)
	li $v0, 4               # system call #4 (print a message)
	la $a0, STR_MESSAGE1    # load sddress of MESSAGE1
	syscall                 # Do it!

	li $v0, 5               # system call #5 (read an integer)
	syscall                 # Do it!
	move $s0, $v0		# copy the input integer to $s0

	li $v0, 4               # system call #4 (print a message)
	la $a0, STR_MESSAGE2    # load sddress of MESSAGE2 (new line)
	syscall                 # Do it!

	blt $s0, $s4, OK_MAX	# check if the entered address does
				# not exceed 33554431

	li $v0, 4               # system call #4 (print a message)
	la $a0, STR_MESSAGE6    # load sddress of MESSAGE6
	syscall                 # Do it!

	j main


OK_MAX: bgt $s0, $zero, POSITIVE # check if the entered address is
				# a positive value

	li $v0, 4               # system call #4 (print a message)
	la $a0, STR_MESSAGE7    # load sddress of MESSAGE7
	syscall                 # Do it!

	j main

POSITIVE:
	li $v0, 4               # system call #4 (print a message)
	la $a0, STR_MESSAGE4    # load sddress of MESSAGE4
	syscall                 # Do it!

	li $v0, 1               # system call #1 (print an integer)
	move $a0, $s0		# copy $s0 to $a0
	syscall                 # Do it!

	li $v0, 4               # system call #4 (print a message)
	la $a0, STR_MESSAGE2    # load sddress of MESSAGE2 (new line)
	syscall                 # Do it!

	li $v0, 4               # system call #4 (print a message)
	la $a0, STR_MESSAGE2    # load sddress of MESSAGE2 (new line)
	syscall                 # Do it!

# Extract the segment number (extract the first 3 bits in the 25 bits) for the segment #

	and $s1, $s0, 0x01000000 # check if the 25th bit is one or zero
	beq $s1, $zero, NO_25BIT

	la  $s2, 4

NO_25BIT: 

	and $s1, $s0, 0x00800000 # check if the 24th bit is one or zero
	beq $s1, $zero, NO_24BIT

	addu  $s2, 2

NO_24BIT: 

	and $s1, $s0, 0x00400000 # check if the 23rd bit is one or zero
	beq $s1, $zero, NO_23BIT

	addu  $s2, 1

NO_23BIT:

	li $v0, 4               # system call #4 (print message)
	la $a0, STR_MESSAGE3    # load sddress of MESSAGE3
	syscall                 # Do it!

	li $v0, 1               # system call #1 (print an integer)
	move $a0, $s2		# copy $s2 to $a0
	syscall                 # Do it!

	li $v0, 4               # system call #4 (print message)
	la $a0, STR_MESSAGE2    # load sddress of MESSAGE2 (new line)
	syscall                 # Do it!

# Extract the offset address

	and $s1, $s0, 0x00000001 # check if the 1st bit is one or zero
	beq $s1, $zero, NO_1BIT

	la  $s3, 1

NO_1BIT:
	and $s1, $s0, 0x00000002 # check if the 2nd bit is one or zero
	beq $s1, $zero, NO_2BIT

	add $s3, 2

NO_2BIT:
	and $s1, $s0, 0x00000004 # check if the 3rd bit is one or zero
	beq $s1, $zero, NO_3BIT

	add $s3, 4

NO_3BIT:
	and $s1, $s0, 0x00000008 # check if the 4th bit is one or zero
	beq $s1, $zero, NO_4BIT

	add $s3, 8

NO_4BIT:
	and $s1, $s0, 0x00000010 # check if the 5th bit is one or zero
	beq $s1, $zero, NO_5BIT

	add $s3, 16

NO_5BIT:
	and $s1, $s0, 0x00000020 # check if the 6th bit is one or zero
	beq $s1, $zero, NO_6BIT

	add $s3, 32

NO_6BIT:
	and $s1, $s0, 0x00000040 # check if the 7th bit is one or zero
	beq $s1, $zero, NO_7BIT

	add $s3, 64

NO_7BIT:
	and $s1, $s0, 0x00000080 # check if the 8th bit is one or zero
	beq $s1, $zero, NO_8BIT

	add $s3, 128

NO_8BIT:
	and $s1, $s0, 0x00000100 # check if the 9th bit is one or zero
	beq $s1, $zero, NO_9BIT

	add $s3, 256

NO_9BIT:
	and $s1, $s0, 0x00000200 # check if the 10th bit is one or zero
	beq $s1, $zero, NO_10BIT

	add $s3, 512

NO_10BIT:
	and $s1, $s0, 0x00000400 # check if the 11th bit is one or zero
	beq $s1, $zero, NO_11BIT

	add $s3, 1024

NO_11BIT:
	and $s1, $s0, 0x00000800 # check if the 12th bit is one or zero
	beq $s1, $zero, NO_12BIT

	add $s3, 2048

NO_12BIT:
	and $s1, $s0, 0x00001000 # check if the 13th bit is one or zero
	beq $s1, $zero, NO_13BIT

	add $s3, 4096

NO_13BIT:
	and $s1, $s0, 0x00002000 # check if the 14th bit is one or zero
	beq $s1, $zero, NO_14BIT

	add $s3, 8192

NO_14BIT:
	and $s1, $s0, 0x00004000 # check if the 15th bit is one or zero
	beq $s1, $zero, NO_15BIT

	add $s3, 16384

NO_15BIT:
	and $s1, $s0, 0x00008000 # check if the 16th bit is one or zero
	beq $s1, $zero, NO_16BIT

	add $s3, 32768

NO_16BIT:
	and $s1, $s0, 0x00010000 # check if the 17th bit is one or zero
	beq $s1, $zero, NO_17BIT

	add $s3, 65536

NO_17BIT:
	and $s1, $s0, 0x00020000 # check if the 18th bit is one or zero
	beq $s1, $zero, NO_18BIT

	add $s3, 131072

NO_18BIT:
	and $s1, $s0, 0x00040000 # check if the 19th bit is one or zero
	beq $s1, $zero, NO_19BIT

	add $s3, 262144

NO_19BIT:
	and $s1, $s0, 0x00080000 # check if the 20th bit is one or zero
	beq $s1, $zero, NO_20BIT

	add $s3, 524288

NO_20BIT:
	and $s1, $s0, 0x00080000 # check if the 20th bit is one or zero
	beq $s1, $zero, NO_21BIT

	add $s3, 1048576

NO_21BIT:
	and $s1, $s0, 0x00080000 # check if the 20th bit is one or zero
	beq $s1, $zero, NO_22BIT

	add $s3, 2097152

NO_22BIT:
	li $v0, 4               # system call #4 (print message)
	la $a0, STR_MESSAGE5    # load sddress of MESSAGE5
	syscall                 # Do it!

	li $v0, 1               # system call #1 (print an integer)
	move $a0, $s3		# copy $s3 to $a0
	syscall                 # Do it!

	li $v0, 4               # system call #4 (print message)
	la $a0, STR_MESSAGE2    # load sddress of MESSAGE2 (new line)
	syscall                 # Do it!	
## END OF OFFSET EXTRACTOR ###################################### 


	
	#############################################################
	# ORIGINAL CODE START:
	#
	#
	#############################################################
CHECK_SEG_TABLE:
	la $t1, SEG_TABLE
	li $t5, 8
	mul $t2, $s2, $t5
	add $t1, $t1, $t2		# Set $t1 to segment BASE
	lw $t3, ($t1)
	add $t1, $t1, 4			# Set $t1 to segment LIMIT
	lw $t4, ($t1)				# Load LIMIT into $t3

	########################################################
	## Output segmentation base/limit for user's benefit
	##
	li $v0, 4
	la $a0, SEG_BASE
	syscall
	li $v0, 1
	move $a0, $t3	# Segment base
	syscall
	li $v0, 4
	la $a0, SEG_LIMIT
	syscall
	li $v0, 1
	move $a0, $t4	# Segment limit
	syscall
	##
	## Output base/limit done
	##########################################################
	
	sub $t0, $t4, $s3		# Subtract OFFSET from segment's LIMIT
	bltz $t0, SEG_FAULT_ERR

	############################################################
	# At this point, $t3 holds segment base
	# and $s3 holds segment limit
	############################################################

	add $s4, $t3, $s3	# Linear Virtual Memory Address is $s4
	li $t2, 32768			# $t2 is 32KB
	div $s4, $t2
	mflo $t0		# $t0 is VM page number

	li $v0, 4
	la $a0, VIRT_PAGE_NO
	syscall
	li $v0, 1
	move $a0, $t0 # Output virtual page number to user
	syscall

	mul $t1, $t2, $t0		# $t1 = 32KB * VM page number
	sub $s0, $s4, $t1		# $s0 = linear VM address - $t1

	li $v0, 4
	la $a0, VIRT_OFF
	syscall
	
	li $v0, 1
	move $a0, $s0
	syscall

	###########################################################
	# Search VMT for page number $t0
	# Offset is $s0
	###########################################################
	la $t1, VMT
	mul $t3, $t0, $t5 	# $t5 is 8
	add $t1, $t1, $t3
	add $s6, $t1, 4
	lw $s5, ($t1)
	
	mul $t3, $s5, $t2
	add $t3, $t3, $s0

	##
	# $s5 is phys page number
	# $s6 is valid flag address	; (extraneous for this project)
	# $t3 is physical address (offset+page*35KB)
	##

	li $v0, 4
	la $a0, PHYS_PAGE
	syscall
	li $v0, 1
	move $a0, $s5		# Print physical page number
	syscall
	li $v0, 4
	la $a0, PHYS_ADDR
	syscall
	li $v0, 1
	move $a0, $t3
	syscall
	
ENDING:	
	li $v0, 4
	la $a0, NEWLINE
	syscall	
	jr $31

SEG_FAULT_ERR:
	li $v0, 4
	la $a0, SEG_FAULT	# Error message
	syscall
	j ENDING	# Terminate if Segmentation Fault

	#############################################################
	# ORIGINAL CODE END:
	#
	#
	#############################################################
