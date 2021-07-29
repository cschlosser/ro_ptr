local Build(image, compiler, cppstd) = {
    name: "build-c++" + cppstd,
    image: image,
    commands: [
      compiler +
      " -std=c++" +
      cppstd +
      " -I include examples/showcase.cc -o ./out-" +
      cppstd,
      "./out-" +
      cppstd
    ]
};

local Pipeline(image, compiler) = 
  std.flatMap(
    function(cppstd) [
      Build(image, compiler, cppstd)
    ],
    ["98", "03", "11", "14", "17"]
  )
;

local Gcc(version) = {
    name: "gcc-" + version,
    kind: "pipeline",
    steps: Pipeline("gcc:" + version, "g++")
};

local Clang(version) = {
    name: "clang-" + version,
    kind: "pipeline",
    steps: Pipeline("silkeh/clang:" + version, "clang++")
};
 
[
  Gcc("latest"),
  Gcc("11"),
  Gcc("10"),
  Gcc("9"),
  Gcc("8"),
  Clang("latest"),
  Clang("12"),
  Clang("11"),
  Clang("10"),
  Clang("9")
]