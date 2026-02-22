#include "tree.h"

int main(){
  TreeNode* src = parse_to_tree("../../file/importantFile/init_data_subject.xml");

  if(src) {
    print_tree(src,0);
  }
  free_tree(src);
  return 0;
}