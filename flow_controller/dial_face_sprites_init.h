ustd::map<uint8_t, const uint16_t(*)[64]> sprite;
ustd::map<uint8_t, bool> is_blank;
const struct Point sprite_coord[256] = {
  {x: 0, y: 0},
  {x: 8, y: 0},
  {x: 16, y: 0},
  {x: 24, y: 0},
  {x: 32, y: 0},
  {x: 40, y: 0},
  {x: 48, y: 0},
  {x: 56, y: 0},
  {x: 64, y: 0},
  {x: 72, y: 0},
  {x: 80, y: 0},
  {x: 88, y: 0},
  {x: 96, y: 0},
  {x: 104, y: 0},
  {x: 112, y: 0},
  {x: 120, y: 0},
  {x: 0, y: 8},
  {x: 8, y: 8},
  {x: 16, y: 8},
  {x: 24, y: 8},
  {x: 32, y: 8},
  {x: 40, y: 8},
  {x: 48, y: 8},
  {x: 56, y: 8},
  {x: 64, y: 8},
  {x: 72, y: 8},
  {x: 80, y: 8},
  {x: 88, y: 8},
  {x: 96, y: 8},
  {x: 104, y: 8},
  {x: 112, y: 8},
  {x: 120, y: 8},
  {x: 0, y: 16},
  {x: 8, y: 16},
  {x: 16, y: 16},
  {x: 24, y: 16},
  {x: 32, y: 16},
  {x: 40, y: 16},
  {x: 48, y: 16},
  {x: 56, y: 16},
  {x: 64, y: 16},
  {x: 72, y: 16},
  {x: 80, y: 16},
  {x: 88, y: 16},
  {x: 96, y: 16},
  {x: 104, y: 16},
  {x: 112, y: 16},
  {x: 120, y: 16},
  {x: 0, y: 24},
  {x: 8, y: 24},
  {x: 16, y: 24},
  {x: 24, y: 24},
  {x: 32, y: 24},
  {x: 40, y: 24},
  {x: 48, y: 24},
  {x: 56, y: 24},
  {x: 64, y: 24},
  {x: 72, y: 24},
  {x: 80, y: 24},
  {x: 88, y: 24},
  {x: 96, y: 24},
  {x: 104, y: 24},
  {x: 112, y: 24},
  {x: 120, y: 24},
  {x: 0, y: 32},
  {x: 8, y: 32},
  {x: 16, y: 32},
  {x: 24, y: 32},
  {x: 32, y: 32},
  {x: 40, y: 32},
  {x: 48, y: 32},
  {x: 56, y: 32},
  {x: 64, y: 32},
  {x: 72, y: 32},
  {x: 80, y: 32},
  {x: 88, y: 32},
  {x: 96, y: 32},
  {x: 104, y: 32},
  {x: 112, y: 32},
  {x: 120, y: 32},
  {x: 0, y: 40},
  {x: 8, y: 40},
  {x: 16, y: 40},
  {x: 24, y: 40},
  {x: 32, y: 40},
  {x: 40, y: 40},
  {x: 48, y: 40},
  {x: 56, y: 40},
  {x: 64, y: 40},
  {x: 72, y: 40},
  {x: 80, y: 40},
  {x: 88, y: 40},
  {x: 96, y: 40},
  {x: 104, y: 40},
  {x: 112, y: 40},
  {x: 120, y: 40},
  {x: 0, y: 48},
  {x: 8, y: 48},
  {x: 16, y: 48},
  {x: 24, y: 48},
  {x: 32, y: 48},
  {x: 40, y: 48},
  {x: 48, y: 48},
  {x: 56, y: 48},
  {x: 64, y: 48},
  {x: 72, y: 48},
  {x: 80, y: 48},
  {x: 88, y: 48},
  {x: 96, y: 48},
  {x: 104, y: 48},
  {x: 112, y: 48},
  {x: 120, y: 48},
  {x: 0, y: 56},
  {x: 8, y: 56},
  {x: 16, y: 56},
  {x: 24, y: 56},
  {x: 32, y: 56},
  {x: 40, y: 56},
  {x: 48, y: 56},
  {x: 56, y: 56},
  {x: 64, y: 56},
  {x: 72, y: 56},
  {x: 80, y: 56},
  {x: 88, y: 56},
  {x: 96, y: 56},
  {x: 104, y: 56},
  {x: 112, y: 56},
  {x: 120, y: 56},
  {x: 0, y: 64},
  {x: 8, y: 64},
  {x: 16, y: 64},
  {x: 24, y: 64},
  {x: 32, y: 64},
  {x: 40, y: 64},
  {x: 48, y: 64},
  {x: 56, y: 64},
  {x: 64, y: 64},
  {x: 72, y: 64},
  {x: 80, y: 64},
  {x: 88, y: 64},
  {x: 96, y: 64},
  {x: 104, y: 64},
  {x: 112, y: 64},
  {x: 120, y: 64},
  {x: 0, y: 72},
  {x: 8, y: 72},
  {x: 16, y: 72},
  {x: 24, y: 72},
  {x: 32, y: 72},
  {x: 40, y: 72},
  {x: 48, y: 72},
  {x: 56, y: 72},
  {x: 64, y: 72},
  {x: 72, y: 72},
  {x: 80, y: 72},
  {x: 88, y: 72},
  {x: 96, y: 72},
  {x: 104, y: 72},
  {x: 112, y: 72},
  {x: 120, y: 72},
  {x: 0, y: 80},
  {x: 8, y: 80},
  {x: 16, y: 80},
  {x: 24, y: 80},
  {x: 32, y: 80},
  {x: 40, y: 80},
  {x: 48, y: 80},
  {x: 56, y: 80},
  {x: 64, y: 80},
  {x: 72, y: 80},
  {x: 80, y: 80},
  {x: 88, y: 80},
  {x: 96, y: 80},
  {x: 104, y: 80},
  {x: 112, y: 80},
  {x: 120, y: 80},
  {x: 0, y: 88},
  {x: 8, y: 88},
  {x: 16, y: 88},
  {x: 24, y: 88},
  {x: 32, y: 88},
  {x: 40, y: 88},
  {x: 48, y: 88},
  {x: 56, y: 88},
  {x: 64, y: 88},
  {x: 72, y: 88},
  {x: 80, y: 88},
  {x: 88, y: 88},
  {x: 96, y: 88},
  {x: 104, y: 88},
  {x: 112, y: 88},
  {x: 120, y: 88},
  {x: 0, y: 96},
  {x: 8, y: 96},
  {x: 16, y: 96},
  {x: 24, y: 96},
  {x: 32, y: 96},
  {x: 40, y: 96},
  {x: 48, y: 96},
  {x: 56, y: 96},
  {x: 64, y: 96},
  {x: 72, y: 96},
  {x: 80, y: 96},
  {x: 88, y: 96},
  {x: 96, y: 96},
  {x: 104, y: 96},
  {x: 112, y: 96},
  {x: 120, y: 96},
  {x: 0, y: 104},
  {x: 8, y: 104},
  {x: 16, y: 104},
  {x: 24, y: 104},
  {x: 32, y: 104},
  {x: 40, y: 104},
  {x: 48, y: 104},
  {x: 56, y: 104},
  {x: 64, y: 104},
  {x: 72, y: 104},
  {x: 80, y: 104},
  {x: 88, y: 104},
  {x: 96, y: 104},
  {x: 104, y: 104},
  {x: 112, y: 104},
  {x: 120, y: 104},
  {x: 0, y: 112},
  {x: 8, y: 112},
  {x: 16, y: 112},
  {x: 24, y: 112},
  {x: 32, y: 112},
  {x: 40, y: 112},
  {x: 48, y: 112},
  {x: 56, y: 112},
  {x: 64, y: 112},
  {x: 72, y: 112},
  {x: 80, y: 112},
  {x: 88, y: 112},
  {x: 96, y: 112},
  {x: 104, y: 112},
  {x: 112, y: 112},
  {x: 120, y: 112},
  {x: 0, y: 120},
  {x: 8, y: 120},
  {x: 16, y: 120},
  {x: 24, y: 120},
  {x: 32, y: 120},
  {x: 40, y: 120},
  {x: 48, y: 120},
  {x: 56, y: 120},
  {x: 64, y: 120},
  {x: 72, y: 120},
  {x: 80, y: 120},
  {x: 88, y: 120},
  {x: 96, y: 120},
  {x: 104, y: 120},
  {x: 112, y: 120},
  {x: 120, y: 120}
};
sprite[7] = &dial_face_7;
sprite[8] = &dial_face_8;
sprite[23] = &dial_face_23;
sprite[24] = &dial_face_24;
sprite[38] = &dial_face_38;
sprite[39] = &dial_face_39;
sprite[40] = &dial_face_40;
sprite[41] = &dial_face_41;
sprite[51] = &dial_face_51;
sprite[52] = &dial_face_52;
sprite[53] = &dial_face_53;
sprite[54] = &dial_face_54;
sprite[55] = &dial_face_55;
sprite[56] = &dial_face_56;
sprite[57] = &dial_face_57;
sprite[58] = &dial_face_58;
sprite[59] = &dial_face_59;
sprite[60] = &dial_face_60;
sprite[67] = &dial_face_67;
sprite[68] = &dial_face_68;
sprite[69] = &dial_face_69;
sprite[70] = &dial_face_70;
sprite[71] = &dial_face_71;
sprite[72] = &dial_face_72;
sprite[74] = &dial_face_74;
sprite[75] = &dial_face_75;
sprite[76] = &dial_face_76;
sprite[81] = &dial_face_81;
sprite[83] = &dial_face_83;
sprite[84] = &dial_face_84;
sprite[86] = &dial_face_86;
sprite[87] = &dial_face_87;
sprite[88] = &dial_face_88;
sprite[89] = &dial_face_89;
sprite[90] = &dial_face_90;
sprite[91] = &dial_face_91;
sprite[92] = &dial_face_92;
sprite[93] = &dial_face_93;
sprite[94] = &dial_face_94;
sprite[95] = &dial_face_95;
sprite[97] = &dial_face_97;
sprite[98] = &dial_face_98;
sprite[99] = &dial_face_99;
sprite[100] = &dial_face_100;
sprite[101] = &dial_face_101;
sprite[103] = &dial_face_103;
sprite[104] = &dial_face_104;
sprite[105] = &dial_face_105;
sprite[106] = &dial_face_106;
sprite[107] = &dial_face_107;
sprite[108] = &dial_face_108;
sprite[109] = &dial_face_109;
sprite[110] = &dial_face_110;
sprite[111] = &dial_face_111;
sprite[114] = &dial_face_114;
sprite[115] = &dial_face_115;
sprite[116] = &dial_face_116;
sprite[117] = &dial_face_117;
sprite[118] = &dial_face_118;
sprite[119] = &dial_face_119;
sprite[120] = &dial_face_120;
sprite[121] = &dial_face_121;
sprite[124] = &dial_face_124;
sprite[125] = &dial_face_125;
sprite[130] = &dial_face_130;
sprite[131] = &dial_face_131;
sprite[134] = &dial_face_134;
sprite[135] = &dial_face_135;
sprite[136] = &dial_face_136;
sprite[137] = &dial_face_137;
sprite[140] = &dial_face_140;
sprite[141] = &dial_face_141;
sprite[146] = &dial_face_146;
sprite[147] = &dial_face_147;
sprite[148] = &dial_face_148;
sprite[151] = &dial_face_151;
sprite[152] = &dial_face_152;
sprite[154] = &dial_face_154;
sprite[155] = &dial_face_155;
sprite[156] = &dial_face_156;
sprite[157] = &dial_face_157;
sprite[163] = &dial_face_163;
sprite[164] = &dial_face_164;
sprite[165] = &dial_face_165;
sprite[166] = &dial_face_166;
sprite[168] = &dial_face_168;
sprite[170] = &dial_face_170;
sprite[171] = &dial_face_171;
sprite[172] = &dial_face_172;
sprite[173] = &dial_face_173;
sprite[179] = &dial_face_179;
sprite[180] = &dial_face_180;
sprite[181] = &dial_face_181;
sprite[182] = &dial_face_182;
sprite[183] = &dial_face_183;
sprite[184] = &dial_face_184;
sprite[185] = &dial_face_185;
sprite[187] = &dial_face_187;
sprite[188] = &dial_face_188;
sprite[189] = &dial_face_189;
sprite[195] = &dial_face_195;
sprite[196] = &dial_face_196;
sprite[197] = &dial_face_197;
sprite[199] = &dial_face_199;
sprite[200] = &dial_face_200;
sprite[201] = &dial_face_201;
sprite[202] = &dial_face_202;
sprite[203] = &dial_face_203;
sprite[204] = &dial_face_204;
sprite[212] = &dial_face_212;
sprite[213] = &dial_face_213;
sprite[215] = &dial_face_215;
sprite[216] = &dial_face_216;
sprite[217] = &dial_face_217;
sprite[218] = &dial_face_218;
sprite[219] = &dial_face_219;
sprite[220] = &dial_face_220;
sprite[228] = &dial_face_228;
sprite[229] = &dial_face_229;
sprite[231] = &dial_face_231;
sprite[232] = &dial_face_232;
sprite[233] = &dial_face_233;
sprite[235] = &dial_face_235;
sprite[236] = &dial_face_236;
sprite[247] = &dial_face_247;
