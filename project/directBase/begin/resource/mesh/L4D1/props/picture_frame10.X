xof 0303txt 0032
template ColorRGBA {
 <35ff44e0-6c7c-11cf-8f52-0040333594a3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <d3e16e81-7835-11cf-8f52-0040333594a3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template Material {
 <3d82ab4d-62da-11cf-ab39-0020af71e433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template TextureFilename {
 <a42790e1-7810-11cf-8f52-0040333594a3>
 STRING filename;
}

template Frame {
 <3d82ab46-62da-11cf-ab39-0020af71e433>
 [...]
}

template Matrix4x4 {
 <f6f23f45-7686-11cf-8f52-0040333594a3>
 array FLOAT matrix[16];
}

template FrameTransformMatrix {
 <f6f23f41-7686-11cf-8f52-0040333594a3>
 Matrix4x4 frameMatrix;
}

template Vector {
 <3d82ab5e-62da-11cf-ab39-0020af71e433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template MeshFace {
 <3d82ab5f-62da-11cf-ab39-0020af71e433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template Mesh {
 <3d82ab44-62da-11cf-ab39-0020af71e433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

template MeshMaterialList {
 <f6f23f42-7686-11cf-8f52-0040333594a3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material <3d82ab4d-62da-11cf-ab39-0020af71e433>]
}

template VertexElement {
 <f752461c-1e23-48f6-b9f8-8350850f336f>
 DWORD Type;
 DWORD Method;
 DWORD Usage;
 DWORD UsageIndex;
}

template DeclData {
 <bf22e553-292c-4781-9fea-62bd554bdd93>
 DWORD nElements;
 array VertexElement Elements[nElements];
 DWORD nDWords;
 array DWORD data[nDWords];
}

template XSkinMeshHeader {
 <3cf169ce-ff7c-44ab-93c0-f78f62d172e2>
 WORD nMaxSkinWeightsPerVertex;
 WORD nMaxSkinWeightsPerFace;
 WORD nBones;
}

template SkinWeights {
 <6f0d123b-bad2-4167-a0d0-80224f25fabb>
 STRING transformNodeName;
 DWORD nWeights;
 array DWORD vertexIndices[nWeights];
 array FLOAT weights[nWeights];
 Matrix4x4 matrixOffset;
}


Material pictures {
 1.000000;1.000000;1.000000;1.000000;;
 32.642128;
 0.025000;0.025000;0.025000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "pictures.tga";
 }
}

Frame dresser1_reference_skeleton {
 

 FrameTransformMatrix {
  39.370080,0.000000,0.000000,0.000000,0.000000,39.370080,0.000006,0.000000,0.000000,-0.000006,39.370080,0.000000,0.000000,0.000000,0.000000,1.000000;;
 }

 Frame static_prop {
  

  FrameTransformMatrix {
   1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,-0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000;;
  }
 }
}

Frame picture_frame10_reference {
 

 FrameTransformMatrix {
  39.370080,0.000000,0.000000,0.000000,0.000000,39.370080,0.000006,0.000000,0.000000,-0.000006,39.370080,0.000000,0.000000,0.000000,0.000000,1.000000;;
 }

 Mesh picture_frame10_reference {
  76;
  -15.852170;17.319094;-1.431874;,
  -16.722734;17.901146;-0.832956;,
  16.592134;17.897274;-0.832954;,
  15.758299;17.318261;-1.431871;,
  17.397174;18.478338;-0.001029;,
  18.127981;-18.977016;-0.421057;,
  18.134499;18.981779;-0.421091;,
  -17.377496;18.481430;-0.001031;,
  -18.120093;18.982906;-0.421098;,
  -17.386333;-18.416733;-0.000879;,
  -18.127752;-18.976267;-0.421071;,
  17.386003;-18.424042;-0.001432;,
  13.891261;15.896064;-0.001646;,
  -14.158163;15.896269;-0.001648;,
  -14.161339;-16.050856;-0.001646;,
  13.882638;-16.060280;-0.001644;,
  13.882638;-16.060280;-0.838289;,
  -14.161339;-16.050856;-0.838291;,
  -14.158163;15.896269;-0.838293;,
  13.891261;15.896064;-0.838291;,
  -14.158163;15.896269;-0.001648;,
  -14.161339;-16.050856;-0.001646;,
  13.882638;-16.060280;-0.001644;,
  13.891261;15.896064;-0.001646;,
  -14.158163;15.896269;-0.838293;,
  -15.852170;17.319094;-1.431874;,
  15.758299;17.318261;-1.431871;,
  13.891261;15.896064;-0.838291;,
  -14.158163;15.896269;-0.838293;,
  -14.161339;-16.050856;-0.838291;,
  -15.857186;-17.352018;-1.431873;,
  -15.852170;17.319094;-1.431874;,
  17.386003;-18.424042;-0.836855;,
  17.397174;18.478341;-0.832954;,
  18.134499;18.981779;-0.421091;,
  18.127981;-18.977016;-0.421057;,
  -15.857186;-17.352018;-1.431873;,
  -14.161339;-16.050856;-0.838291;,
  13.882638;-16.060280;-0.838289;,
  15.754094;-17.355974;-1.431867;,
  15.758299;17.318261;-1.431871;,
  15.754094;-17.355974;-1.431867;,
  13.882638;-16.060280;-0.838289;,
  13.891261;15.896064;-0.838291;,
  17.397174;18.478341;-0.832954;,
  -17.377496;18.481430;-0.832956;,
  -18.120093;18.982906;-0.421098;,
  18.134499;18.981779;-0.421091;,
  -17.386333;-18.416733;-0.831517;,
  17.386003;-18.424042;-0.836855;,
  18.127981;-18.977016;-0.421057;,
  -18.127752;-18.976267;-0.421071;,
  15.758299;17.318261;-1.431871;,
  16.592134;17.897274;-0.832954;,
  16.583790;-17.979355;-0.836854;,
  15.754094;-17.355974;-1.431867;,
  -17.377496;18.481430;-0.832956;,
  -17.386333;-18.416733;-0.831517;,
  -18.127752;-18.976267;-0.421071;,
  -18.120093;18.982906;-0.421098;,
  -15.852170;17.319094;-1.431874;,
  -15.857186;-17.352018;-1.431873;,
  -16.728590;-17.965032;-0.831516;,
  -16.722734;17.901146;-0.832956;,
  -16.728590;-17.965032;-0.831516;,
  -15.857186;-17.352018;-1.431873;,
  15.754094;-17.355974;-1.431867;,
  16.583790;-17.979355;-0.836854;,
  -16.728590;-17.965032;-0.831516;,
  17.386003;-18.424042;-0.836855;,
  -17.386333;-18.416733;-0.831517;,
  -16.722734;17.901146;-0.832956;,
  -17.377496;18.481430;-0.832956;,
  16.592134;17.897274;-0.832954;,
  17.397174;18.478341;-0.832954;,
  16.583790;-17.979355;-0.836854;;
  52;
  3;0,1,2;,
  3;0,2,3;,
  3;4,5,6;,
  3;7,4,6;,
  3;7,6,8;,
  3;9,7,8;,
  3;9,8,10;,
  3;11,9,10;,
  3;11,10,5;,
  3;4,11,5;,
  3;12,11,4;,
  3;7,12,4;,
  3;7,13,12;,
  3;9,13,7;,
  3;9,14,13;,
  3;14,9,11;,
  3;14,11,15;,
  3;12,15,11;,
  3;16,17,18;,
  3;16,18,19;,
  3;20,21,22;,
  3;20,22,23;,
  3;24,25,26;,
  3;24,26,27;,
  3;28,29,30;,
  3;28,30,31;,
  3;32,33,34;,
  3;32,34,35;,
  3;36,37,38;,
  3;36,38,39;,
  3;40,41,42;,
  3;40,42,43;,
  3;44,45,46;,
  3;44,46,47;,
  3;48,49,50;,
  3;48,50,51;,
  3;52,53,54;,
  3;52,54,55;,
  3;56,57,58;,
  3;56,58,59;,
  3;60,61,62;,
  3;60,62,63;,
  3;64,65,66;,
  3;64,66,67;,
  3;68,69,70;,
  3;71,68,70;,
  3;71,70,72;,
  3;73,71,72;,
  3;73,72,74;,
  3;75,73,74;,
  3;75,74,69;,
  3;68,75,69;;

  MeshMaterialList {
   1;
   52;
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0;
   { pictures }
  }

  DeclData {
   4;
   2;0;3;0;,
   2;0;6;0;,
   2;0;7;0;,
   1;0;5;0;;
   836;
   943015369,
   1060626727,
   3207732477,
   1065353216,
   938111764,
   952027077,
   951177277,
   3207732477,
   3208110376,
   1061300646,
   1057175044,
   942912033,
   1060626971,
   3207732226,
   1065353216,
   938543259,
   952064534,
   951279357,
   3207732226,
   3208110619,
   1061254307,
   1057111895,
   947739394,
   1060618932,
   3207740520,
   1065353216,
   3086720338,
   946483186,
   933299712,
   3207740520,
   3208102580,
   1063027743,
   1057112314,
   948041793,
   1060618213,
   3207741261,
   1065353216,
   3087602717,
   946340948,
   932064833,
   3207741262,
   3208101860,
   1062983350,
   1057175128,
   1040688748,
   1043343534,
   1064952979,
   1065197549,
   1005304306,
   3188390237,
   3170421152,
   1065102655,
   3190656110,
   1063070592,
   1057049266,
   1049185283,
   3198655397,
   1063777001,
   1064660220,
   3137051633,
   3197215004,
   1036140842,
   1064428757,
   1050700759,
   1063109498,
   1061113010,
   1049259641,
   1051970756,
   1063615503,
   1064631033,
   998511101,
   3197408865,
   3185057344,
   1064284548,
   3198910618,
   1063109851,
   1056994639,
   3188152127,
   1043347641,
   1064953485,
   1065198342,
   3152398370,
   1040884050,
   1022815973,
   1065102498,
   3190662480,
   1061219461,
   1057048930,
   3196723267,
   1051973442,
   1063617992,
   1064634085,
   3146149579,
   1049905032,
   1037557212,
   1064284039,
   3198914762,
   1061179917,
   1056994522,
   3188096360,
   3190058530,
   1064988248,
   1065200855,
   1005802963,
   1040808692,
   3169590912,
   1065135036,
   1042411567,
   1061218991,
   1061052226,
   3196652768,
   3198650812,
   1063780219,
   1064662929,
   989044620,
   1049713090,
   3183588003,
   1064429553,
   1050698715,
   1061179514,
   1061112926,
   1040630795,
   3190064079,
   1064987412,
   1065200329,
   3152844113,
   3188308605,
   1022025714,
   1065134836,
   1042418411,
   1063070005,
   1061053014,
   3094365003,
   3100601311,
   1065353216,
   1065353216,
   914945528,
   946881466,
   3062441636,
   1065353216,
   953117631,
   1062883962,
   1057329428,
   949187527,
   3099687679,
   1065353216,
   1065353216,
   908250977,
   3096671144,
   3055706096,
   1065353216,
   952204054,
   1061390823,
   1057329412,
   951835129,
   955773610,
   1065353216,
   1065353216,
   3068962516,
   3099318662,
   921455584,
   1065353216,
   3103257344,
   1061390656,
   1060795534,
   3081697564,
   941139423,
   1065353216,
   1065353216,
   3056094736,
   934213966,
   908614424,
   1065353216,
   3088623056,
   1062883509,
   1060796558,
   865643735,
   3012214711,
   3212836864,
   1065353216,
   3040141786,
   865643741,
   3040141786,
   3212836864,
   864731057,
   1062883509,
   1060796558,
   865506086,
   3012814491,
   3212836864,
   1065353216,
   889562399,
   865506081,
   889562400,
   3212836864,
   865330848,
   1061390656,
   1060795534,
   865668568,
   3012106505,
   3212836864,
   1065353216,
   3043853955,
   865668576,
   3043853956,
   3212836864,
   864622848,
   1061390823,
   1057329412,
   865806171,
   3011503582,
   3212836864,
   1065353216,
   3054091291,
   865806188,
   3054091291,
   3212836864,
   864019893,
   1062883962,
   1057329428,
   949187527,
   3099687679,
   1065353216,
   1065353216,
   3026012991,
   3096671178,
   878985808,
   1065353216,
   952204029,
   1059826029,
   1057144896,
   951835129,
   955773610,
   1065353216,
   1065353216,
   909074630,
   3099318820,
   3056604852,
   1065353216,
   3103257226,
   1059825878,
   1061036623,
   3081697564,
   941139423,
   1065353216,
   1065353216,
   881029680,
   934213911,
   3028486624,
   1065353216,
   3088623072,
   1061034190,
   1061037780,
   3094365003,
   3100601311,
   1065353216,
   1065353216,
   3056644983,
   946881284,
   909136417,
   1065353216,
   953117683,
   1061034559,
   1057144912,
   3072725305,
   3200590699,
   3211543368,
   1065353216,
   3053179059,
   3072773861,
   906802508,
   3211543368,
   1053107051,
   1061390823,
   1057329412,
   3072896596,
   3200590605,
   3211543388,
   1065353216,
   3053132013,
   3072961907,
   907113696,
   3211543388,
   1053106956,
   1061300646,
   1057175044,
   3059677321,
   3200594676,
   3211542538,
   1065353216,
   3054072872,
   3057139316,
   3042937968,
   3211542538,
   1053111028,
   1062983350,
   1057175128,
   3057290384,
   3200595005,
   3211542469,
   1065353216,
   3054143286,
   3054523396,
   3046146104,
   3211542469,
   1053111357,
   1062883962,
   1057329428,
   1051248665,
   921699328,
   3211899062,
   1064415414,
   3071232000,
   1051248665,
   3065998400,
   3212836864,
   3072362585,
   1061390823,
   1057329412,
   1051306799,
   3099614568,
   3211888883,
   1064405235,
   940188890,
   1051306799,
   892736256,
   3212836864,
   952918660,
   1061390656,
   1060795534,
   1051308814,
   3100126169,
   3211888529,
   1064404881,
   939547288,
   1051308814,
   3057220384,
   3212836864,
   953295021,
   1061300377,
   1060936698,
   1051251908,
   905999575,
   3211898496,
   1064414848,
   3072423303,
   1051251909,
   3071137476,
   3212836864,
   3064405534,
   1061300646,
   1057175044,
   1056588905,
   3098607929,
   3210695992,
   1063212344,
   917481473,
   1056588906,
   3088704198,
   3212836864,
   949995717,
   1063070005,
   1061053014,
   1056551744,
   3093834112,
   3210706387,
   1063222739,
   3096098836,
   1056551744,
   3098654532,
   3212836864,
   931577896,
   1063070592,
   1057049266,
   1056552572,
   3094011757,
   3210706156,
   1063222508,
   3095881026,
   1056552572,
   3098507766,
   3212836864,
   932311672,
   1063109851,
   1056994639,
   1056589299,
   3098650353,
   3210695882,
   1063212234,
   918994810,
   1056589299,
   3088580926,
   3212836864,
   950078893,
   1063109498,
   1061113010,
   953429594,
   1054133218,
   3211319185,
   1065353216,
   929797761,
   955694495,
   948000157,
   3211319185,
   3201616865,
   1061300377,
   1060936698,
   952980080,
   1054135261,
   3211318718,
   1065353216,
   932519176,
   955435405,
   948360094,
   3211318718,
   3201618909,
   1061390656,
   1060795534,
   951303351,
   1054143088,
   3211316929,
   1065353216,
   3074188001,
   951771001,
   937507632,
   3211316929,
   3201626736,
   1062883509,
   1060796558,
   951066828,
   1054144161,
   3211316683,
   1065353216,
   3074140485,
   951513772,
   937102925,
   3211316683,
   3201627809,
   1062983132,
   1060937134,
   3197813325,
   940335536,
   3212052099,
   1064568451,
   925496651,
   3197813325,
   3036090432,
   3212836864,
   3088230527,
   1062983350,
   1057175128,
   3197836263,
   949944811,
   3212048458,
   1064564810,
   3066738216,
   3197836262,
   3086023390,
   3212836864,
   3096687223,
   1062983132,
   1060937134,
   3197839990,
   950870152,
   3212047865,
   1064564217,
   3065711892,
   3197839990,
   3086905115,
   3212836864,
   3097588025,
   1062883509,
   1060796558,
   3197814853,
   941104691,
   3212051857,
   1064568209,
   926632200,
   3197814853,
   3031274752,
   3212836864,
   3089049508,
   1062883962,
   1057329428,
   939600920,
   1059206691,
   3209038993,
   1065353216,
   3070763434,
   940251196,
   930560580,
   3209038993,
   3206690338,
   1063070592,
   1057049266,
   943313651,
   1059216236,
   3209031169,
   1065353216,
   923066471,
   948292535,
   943940724,
   3209031168,
   3206699885,
   1061219461,
   1057048930,
   943073449,
   1059215575,
   3209031711,
   1065353216,
   922981382,
   948128060,
   943715044,
   3209031710,
   3206699224,
   1061179917,
   1056994522,
   939505214,
   1059206495,
   3209039153,
   1065353216,
   3070750292,
   940142303,
   930294243,
   3209039153,
   3206690143,
   1063109851,
   1056994639,
   3104141087,
   3206062426,
   3209528850,
   1065353216,
   3096212619,
   3101956685,
   926540782,
   3209528850,
   1058578778,
   1061218991,
   1061052226,
   3104237088,
   3206063030,
   3209528402,
   1065353216,
   949301445,
   3110039594,
   960568337,
   3209528401,
   1058579382,
   1063070005,
   1061053014,
   3104239455,
   3206063304,
   3209528198,
   1065353216,
   948797487,
   3109855708,
   960256587,
   3209528198,
   1058579656,
   1063109498,
   1061113010,
   3104154946,
   3206062391,
   3209528876,
   1065353216,
   3096386071,
   3101862393,
   924976697,
   3209528876,
   1058578743,
   1061179514,
   1061112926,
   1058348610,
   3098007257,
   3209696769,
   1062213121,
   946328448,
   1058348610,
   3051552760,
   3212836864,
   952889789,
   1062983350,
   1057175128,
   1058348762,
   3097962048,
   3209696660,
   1062213012,
   946745142,
   1058348762,
   3029348384,
   3212836864,
   952974401,
   1063027743,
   1057112314,
   1058368125,
   3089220567,
   3209682763,
   1062199115,
   3090513847,
   1058368125,
   3094465242,
   3212836864,
   919297272,
   1063027290,
   1061004763,
   1058367813,
   3089404576,
   3209682987,
   1062199339,
   3091344902,
   1058367813,
   3095247427,
   3212836864,
   916615248,
   1062983132,
   1060937134,
   3203921071,
   950557754,
   3210738173,
   1063254525,
   897099071,
   3203921071,
   3089083324,
   3212836864,
   3096722836,
   1061219461,
   1057048930,
   3203949479,
   953618656,
   3210730302,
   1063246654,
   950151919,
   3203949479,
   932569343,
   3212836864,
   3104136735,
   1061218991,
   1061052226,
   3203949930,
   953674628,
   3210730176,
   1063246529,
   949903615,
   3203949930,
   931591147,
   3212836864,
   3104100994,
   1061179514,
   1061112926,
   3203918468,
   950284699,
   3210738894,
   1063255246,
   874354730,
   3203918467,
   3089004643,
   3212836864,
   3096432513,
   1061179917,
   1056994522,
   3205579043,
   951014496,
   3209874716,
   1062391068,
   3074430049,
   3205579043,
   3094249845,
   3212836864,
   3095576611,
   1061300646,
   1057175044,
   3205569460,
   948134274,
   3209881314,
   1062397666,
   3102353446,
   3205569460,
   3104157770,
   3212836864,
   927198432,
   1061300377,
   1060936698,
   3205566513,
   946690935,
   3209883341,
   1062399693,
   3101969448,
   3205566513,
   3103742807,
   3212836864,
   930915024,
   1061254005,
   1061003220,
   3205580216,
   951369101,
   3209873907,
   1062390259,
   3072722737,
   3205580216,
   3094302308,
   3212836864,
   3095989033,
   1061254307,
   1057111895,
   3112569643,
   3207720967,
   3208121514,
   1065353215,
   3101730420,
   3112445400,
   953017732,
   3208121514,
   1060237319,
   1061254005,
   1061003220,
   3112550328,
   3207720838,
   3208121638,
   1065353215,
   3102703712,
   3112183247,
   951588762,
   3208121639,
   1060237190,
   1061300377,
   1060936698,
   3112514839,
   3207721388,
   3208121106,
   1065353214,
   953715505,
   3119358298,
   969676862,
   3208121108,
   1060237738,
   1062983132,
   1060937134,
   3112529720,
   3207721445,
   3208121052,
   1065353214,
   954014566,
   3119451372,
   969795348,
   3208121053,
   1060237794,
   1063027290,
   1061004763,
   3096537599,
   953508712,
   3212836864,
   1065353216,
   924345204,
   3096537472,
   924337446,
   3212836864,
   3100992446,
   1061254005,
   1061003220,
   3075837342,
   3079271150,
   3212836864,
   1065353216,
   940302268,
   3075837945,
   940302324,
   3212836864,
   931787268,
   1063070005,
   1061053014,
   3090065694,
   948015416,
   3212836864,
   1065353216,
   929098999,
   3090065466,
   929096170,
   3212836864,
   3095499141,
   1061218991,
   1061052226,
   3079334553,
   3080649104,
   3212836864,
   1065353216,
   943463545,
   3079335020,
   943463630,
   3212836864,
   933165048,
   1061254307,
   1057111895,
   3080444359,
   3081750707,
   3212836864,
   1065353216,
   944857707,
   3080444934,
   944857816,
   3212836864,
   934266549,
   1061219461,
   1057048930,
   3088663649,
   945008450,
   3212836864,
   1065353216,
   3084853375,
   3088664018,
   3084854390,
   3212836864,
   3092491831,
   1063027743,
   1057112314,
   3091072845,
   948491297,
   3212836864,
   1065353216,
   3087664030,
   3091073435,
   3087664842,
   3212836864,
   3095974740,
   1063070592,
   1057049266,
   3095950736,
   3102663342,
   3212836864,
   1065353216,
   933782536,
   3095951050,
   933786609,
   3212836864,
   955179514,
   1063027290,
   1061004763;
  }

  XSkinMeshHeader {
   1;
   1;
   1;
  }

  SkinWeights {
   "static_prop";
   76;
   0,
   1,
   2,
   3,
   4,
   5,
   6,
   7,
   8,
   9,
   10,
   11,
   12,
   13,
   14,
   15,
   16,
   17,
   18,
   19,
   20,
   21,
   22,
   23,
   24,
   25,
   26,
   27,
   28,
   29,
   30,
   31,
   32,
   33,
   34,
   35,
   36,
   37,
   38,
   39,
   40,
   41,
   42,
   43,
   44,
   45,
   46,
   47,
   48,
   49,
   50,
   51,
   52,
   53,
   54,
   55,
   56,
   57,
   58,
   59,
   60,
   61,
   62,
   63,
   64,
   65,
   66,
   67,
   68,
   69,
   70,
   71,
   72,
   73,
   74,
   75;
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000;
   1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,-0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000;;
  }
 }
}