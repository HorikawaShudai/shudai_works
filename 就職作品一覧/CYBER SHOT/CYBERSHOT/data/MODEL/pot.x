xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 130;
 -9.15970;39.18944;-9.23299;,
 9.47572;39.18944;-9.23299;,
 9.47572;1.64433;-9.23299;,
 -9.15970;1.64433;-9.23299;,
 9.47572;39.18944;-9.23299;,
 9.47572;39.18944;9.23299;,
 9.47572;1.64433;9.23299;,
 9.47572;1.64433;-9.23299;,
 9.47572;39.18944;9.23299;,
 -9.15970;39.18944;9.23299;,
 -9.15970;1.64433;9.23299;,
 9.47572;1.64433;9.23299;,
 -9.15970;39.18944;9.23299;,
 -9.15970;39.18944;-9.23299;,
 -9.15970;1.64433;-9.23299;,
 -9.15970;1.64433;9.23299;,
 9.47572;39.18944;-9.23299;,
 -9.15970;39.18944;-9.23299;,
 -9.15970;1.64433;-9.23299;,
 9.47572;1.64433;-9.23299;,
 0.00000;47.77004;-3.47372;,
 2.99863;47.77004;-2.45629;,
 2.99863;42.86999;-2.45629;,
 0.00000;42.86999;-3.47372;,
 4.24070;47.77004;0.00000;,
 4.24070;42.86999;0.00000;,
 2.99863;47.77004;2.45629;,
 2.99863;42.86999;2.45629;,
 -0.00000;47.77004;3.47372;,
 -0.00000;42.86999;3.47372;,
 -2.99863;47.77004;2.45629;,
 -2.99863;42.86999;2.45629;,
 -4.24070;47.77004;-0.00000;,
 -4.24070;42.86999;-0.00000;,
 -2.99863;47.77004;-2.45629;,
 -2.99863;42.86999;-2.45629;,
 0.00000;47.77004;-3.47372;,
 0.00000;42.86999;-3.47372;,
 0.00000;47.77004;0.00000;,
 0.00000;47.77004;0.00000;,
 0.00000;47.77004;0.00000;,
 0.00000;47.77004;0.00000;,
 0.00000;47.77004;0.00000;,
 0.00000;47.77004;0.00000;,
 0.00000;47.77004;0.00000;,
 0.00000;47.77004;0.00000;,
 0.00000;42.86999;0.00000;,
 0.00000;42.86999;0.00000;,
 0.00000;42.86999;0.00000;,
 0.00000;42.86999;0.00000;,
 0.00000;42.86999;0.00000;,
 0.00000;42.86999;0.00000;,
 0.00000;42.86999;0.00000;,
 0.00000;42.86999;0.00000;,
 -10.00000;43.18324;-10.00000;,
 10.00000;43.18324;-10.00000;,
 10.00000;39.14935;-10.00000;,
 -10.00000;39.14935;-10.00000;,
 10.00000;43.18324;-10.00000;,
 10.00000;43.18324;10.00000;,
 10.00000;39.14935;10.00000;,
 10.00000;39.14935;-10.00000;,
 10.00000;43.18324;10.00000;,
 -10.00000;43.18324;10.00000;,
 -10.00000;39.14935;10.00000;,
 10.00000;39.14935;10.00000;,
 -10.00000;43.18324;10.00000;,
 -10.00000;43.18324;-10.00000;,
 -10.00000;39.14935;-10.00000;,
 -10.00000;39.14935;10.00000;,
 10.00000;43.18324;-10.00000;,
 -10.00000;43.18324;-10.00000;,
 -10.00000;39.14935;-10.00000;,
 10.00000;39.14935;-10.00000;,
 -10.00000;1.46910;-10.00000;,
 10.00000;1.46910;-10.00000;,
 10.00000;0.24031;-10.00000;,
 -10.00000;0.24031;-10.00000;,
 10.00000;1.46910;-10.00000;,
 10.00000;1.46910;10.00000;,
 10.00000;0.24031;10.00000;,
 10.00000;0.24031;-10.00000;,
 10.00000;1.46910;10.00000;,
 -10.00000;1.46910;10.00000;,
 -10.00000;0.24031;10.00000;,
 10.00000;0.24031;10.00000;,
 -10.00000;1.46910;10.00000;,
 -10.00000;1.46910;-10.00000;,
 -10.00000;0.24031;-10.00000;,
 -10.00000;0.24031;10.00000;,
 10.00000;1.46910;-10.00000;,
 -10.00000;1.46910;-10.00000;,
 -10.00000;0.24031;-10.00000;,
 10.00000;0.24031;-10.00000;,
 -10.00000;43.18324;-10.00000;,
 10.00000;43.18324;-10.00000;,
 10.00000;39.14935;-10.00000;,
 -10.00000;39.14935;-10.00000;,
 10.00000;43.18324;-10.00000;,
 10.00000;43.18324;10.00000;,
 10.00000;39.14935;10.00000;,
 10.00000;39.14935;-10.00000;,
 10.00000;43.18324;10.00000;,
 -10.00000;43.18324;10.00000;,
 -10.00000;39.14935;10.00000;,
 10.00000;39.14935;10.00000;,
 -10.00000;43.18324;10.00000;,
 -10.00000;43.18324;-10.00000;,
 -10.00000;39.14935;-10.00000;,
 -10.00000;39.14935;10.00000;,
 10.00000;43.18324;-10.00000;,
 -10.00000;43.18324;-10.00000;,
 -10.00000;39.14935;-10.00000;,
 10.00000;39.14935;-10.00000;,
 -10.00000;39.75133;-9.41900;,
 10.00000;39.75133;-9.41900;,
 10.00000;1.26290;-9.59353;,
 -10.00000;1.26290;-9.59353;,
 -9.59199;39.75133;9.86150;,
 -9.59198;39.75133;-10.13850;,
 -9.76652;1.26290;-10.13850;,
 -9.76652;1.26290;9.86150;,
 10.26877;39.75133;9.80202;,
 -9.73046;39.75133;9.97655;,
 -9.72893;1.26290;10.15107;,
 10.27029;1.26290;9.97655;,
 9.83099;39.75133;-9.79740;,
 9.66830;39.75133;10.19041;,
 9.70895;1.26290;10.19649;,
 9.87164;1.26290;-9.79131;;
 
 52;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;12,5,16,17;,
 4;18,19,6,15;,
 4;20,21,22,23;,
 4;21,24,25,22;,
 4;24,26,27,25;,
 4;26,28,29,27;,
 4;28,30,31,29;,
 4;30,32,33,31;,
 4;32,34,35,33;,
 4;34,36,37,35;,
 3;38,21,20;,
 3;39,24,21;,
 3;40,26,24;,
 3;41,28,26;,
 3;42,30,28;,
 3;43,32,30;,
 3;44,34,32;,
 3;45,36,34;,
 3;46,23,22;,
 3;47,22,25;,
 3;48,25,27;,
 3;49,27,29;,
 3;50,29,31;,
 3;51,31,33;,
 3;52,33,35;,
 3;53,35,37;,
 4;54,55,56,57;,
 4;58,59,60,61;,
 4;62,63,64,65;,
 4;66,67,68,69;,
 4;66,59,70,71;,
 4;72,73,60,69;,
 4;74,75,76,77;,
 4;78,79,80,81;,
 4;82,83,84,85;,
 4;86,87,88,89;,
 4;86,79,90,91;,
 4;92,93,80,89;,
 4;94,95,96,97;,
 4;98,99,100,101;,
 4;102,103,104,105;,
 4;106,107,108,109;,
 4;106,99,110,111;,
 4;112,113,100,109;,
 4;114,115,116,117;,
 4;118,119,120,121;,
 4;122,123,124,125;,
 4;126,127,128,129;;
 
 MeshMaterialList {
  3;
  52;
  1,
  1,
  1,
  1,
  1,
  1,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.800000;0.800000;0.500000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.101961;1.000000;0.054902;0.360000;;
   100.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  38;
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;0.000000;,
  -0.000000;0.000000;-1.000000;,
  0.655516;0.000000;-0.755181;,
  1.000000;0.000000;0.000000;,
  0.655516;0.000000;0.755181;,
  -0.000000;0.000000;1.000000;,
  -0.655517;0.000000;0.755181;,
  -1.000000;0.000000;0.000000;,
  -0.655516;0.000000;-0.755181;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.004535;-0.999990;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  -0.999990;0.004535;-0.000000;,
  0.008726;0.004535;0.999952;,
  0.999966;0.001057;0.008139;;
  52;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;7,8,8,7;,
  4;8,9,9,8;,
  4;9,10,10,9;,
  4;10,11,11,10;,
  4;11,12,12,11;,
  4;12,13,13,12;,
  4;13,14,14,13;,
  4;14,7,7,14;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  4;16,16,16,16;,
  4;17,17,17,17;,
  4;18,18,18,18;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;21,21,21,21;,
  4;22,22,22,22;,
  4;23,23,23,23;,
  4;24,24,24,24;,
  4;25,25,25,25;,
  4;26,26,26,26;,
  4;27,27,27,27;,
  4;28,28,28,28;,
  4;29,29,29,29;,
  4;30,30,30,30;,
  4;32,32,32,32;,
  4;33,33,33,33;,
  4;34,34,34,34;,
  4;31,31,31,31;,
  4;35,35,35,35;,
  4;36,36,36,36;,
  4;37,37,37,37;;
 }
 MeshTextureCoords {
  130;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;;
 }
}
