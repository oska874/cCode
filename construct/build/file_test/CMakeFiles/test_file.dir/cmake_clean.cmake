FILE(REMOVE_RECURSE
  "CMakeFiles/test_file.dir/test_file.c.o"
  "libtest_file.pdb"
  "libtest_file.a"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang C)
  INCLUDE(CMakeFiles/test_file.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
