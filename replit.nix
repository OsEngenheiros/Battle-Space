{ pkgs }: {
  deps = [
    pkgs.clang_12
    pkgs.ccls
    pkgs.gdb
    pkgs.raylib
    pkgs.xorg.libX11
    pkgs.xorg.libXcursor
    pkgs.xorg.libXinerama
    pkgs.xorg.libXrandr
    pkgs.xorg.libXi
    pkgs.libGL
  ];
}
