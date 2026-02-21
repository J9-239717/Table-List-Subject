#include "tree.h"

static Attribute* create_attribute(char* name, char* value) {
    Attribute* attr = (Attribute*)malloc(sizeof(Attribute));
    attr->name = strdup(name);
    attr->value = strdup(value);
    attr->next = NULL;
    return attr;
}

static TreeNode* create_tree_node(char* tag_name, char* text, TreeNode* parent) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->tag_name = strdup(tag_name);
    node->attributes = NULL;
    node->text = text ? strdup(text) : NULL;
    node->first_child = NULL;
    node->next_sibling = NULL;
    node->parent = parent;
    return node;
}

static void add_child(TreeNode* parent, TreeNode* child) {
    if (parent->first_child == NULL) {
        parent->first_child = child;
    }
    else {
        TreeNode* sibling = parent->first_child;
        while (sibling->next_sibling != NULL) {
            sibling = sibling->next_sibling;
        }
        sibling->next_sibling = child;
    }
}


void free_tree(TreeNode* node) {
    if (node == NULL) return;
    free_tree(node->first_child);
    free_tree(node->next_sibling);
    free(node->tag_name);
    if (node->text) free(node->text);
    Attribute* attr = node->attributes;
    while (attr != NULL) {
        Attribute* next = attr->next;
        free(attr->name);
        free(attr->value);
        free(attr);
        attr = next;
    }
    free(node);
}

static char* read_until(const char** str, char delimiter) {
    int capacity = 1 << 8;
    char* buffer = (char*)malloc(capacity);
    int length = 0;
    char ch;
    while ((ch = **str) != '\0' && ch != delimiter) {
        if (length + 1 >= capacity) {
            capacity *= 2;
            buffer = (char*)realloc(buffer, capacity);
        }
        buffer[length++] = ch;
        (*str)++;
    }
    if (ch == delimiter) {
        if (length + 1 >= capacity) {
          capacity *= 2;
          buffer = (char*)realloc(buffer, capacity);
        }
        buffer[length++] = ch;
        (*str)++;
    }
    buffer[length] = '\0';
    return buffer;
}
// skip until found [des] and skip str to end of des
static void skip_until(const char** str, const char* des) {
  int lenght_des = strlen(des);
  while(**str != '\0') {
    if(strncmp(*str,des,lenght_des) != 0) (*str)++;
    else {
      for(int i = 0; i < lenght_des; i++) {
        ++(*str);
        if(**str == '\0') return;
      }
      return;
    }
  }
  return;
}

// return save ptr last read if is '\0' return NULL
static char* read_until_with_quotes(const char* src, const char delimiter,char* buffer,size_t max_buffer_size) {
  if (!src || max_buffer_size == 0) { 
      if (buffer) buffer[0] = '\0';
      return NULL;
  }
  const char* ptr = src;
  size_t i = 0;
  bool in_quotes = false;

  while(*ptr != '\0') {
    if(*ptr == '\"') {
      in_quotes = !in_quotes;
    }

    if(*ptr != delimiter || in_quotes) {
      if (i < max_buffer_size - 1) {
        buffer[i++] = *ptr;
      }
    }else {
      break;
    }
    ptr++;
  }
  buffer[i] = '\0';
  if(*ptr == '\0' || *(ptr+1) == '\0') return NULL;
  return (char*)(ptr+1);
}

static void remove_newlines(char* str) {
    char *p = str;
    char *q = str;
    while (*q != '\0'){
        if(*q != '\n' && *q != '\r'){
            *p++ = *q;
        }
        q++;
    }
    *p = '\0';

    char* start = str;
    while(isspace((unsigned char)*start))start++;

    char* end = str + strlen(str) - 1;
    while(end > start &&isspace((unsigned char)*end))end--;

    size_t final_lenght = end - start + 1;
    memmove(str,start,final_lenght);
    str[final_lenght] = '\0';
}

static int is_self_closing_tag(const char* tag_name) {
    const char* Isselfclosingtag[] = {"area", "base", "br", "col", "embed", "hr", "img", "input", "link", "meta", "param", "wbr"};
    size_t size_tag = sizeof(Isselfclosingtag) / sizeof(Isselfclosingtag[0]);
    for(size_t i = 0; i < size_tag; i++){
        if(strcmp(tag_name,Isselfclosingtag[i]) == 0) return 1;
    }
    return 0;
}

void print_tree(TreeNode* node, int depth) {
    if (node == NULL) return;
    for (int i = 0; i < depth; i++) printf("  ");
    printf("<%s", node->tag_name);
    Attribute* attr = node->attributes;
    while (attr != NULL) {
        printf(" %s=\"%s\"", attr->name, attr->value);
        attr = attr->next;
    }
    printf(">");
    bool isContainText = false;
    if (node->text)
    {
        printf("%s", node->text);
        isContainText = true;
    }
    else
        printf("\n");
    
    print_tree(node->first_child, depth + 1);
        
    if (!is_self_closing_tag(node->tag_name)) {
        if(!isContainText) for (int i = 0; i < depth; i++) printf("  ");
        printf("</%s>\n", node->tag_name);
    }
    print_tree(node->next_sibling, depth);
}

static int check_self_close_tag(const char* src) {
  const char* ptr = src;
  const char* last_char = NULL;
  bool in_quotes = false;

  while(*ptr != '\0') {
    if(*ptr == '\"') {
      in_quotes = !in_quotes;
    }

    if(*ptr == '>' && !in_quotes) {
      if(last_char != NULL && *last_char == '/') {
        return true;
      }
      break;
    }

    if(*ptr != ' ' && *ptr != '\t') {
      last_char = ptr;
    }
    ptr++;
  }
  return false;
}

static int is_skip_tag(const char* src) {
  const char* tags[] = {
    "script"
  };
  const int c_tags = 1;
  for(int i = 0 ; i < c_tags; i++) {
    if(strncmp(src, tags[i],strlen(tags[i])) == 0) return 1;
  }
  return 0;
}

static Attribute* parse_attribute(const char* src) {
  char name[1 << 8];
  size_t i = 0;
  size_t j = 0;
  if(src[0] == '/') return NULL;
  while(src[i] != '\0' && src[i] != '=') name[j++] = src[i++];
  if(src[i] == '\0')  {
    printf("parse attribute: not correcly syntax can't find = in src = %s \n", src);
    exit(EXIT_FAILURE);
  }
  i += 2; // skip '=' and '/"'
  name[j] = '\0';

  size_t init_len = 1 << 16;
  char* value = (char*)malloc(init_len);
  if(!value) {
    printf("parse_attribute: Not enought memory\n");
    exit(EXIT_FAILURE);
  }
  j = 0;
  while(src[i] != '\0' && src[i] != '\"') {
    if(j + 1 >= init_len) {
      init_len *= 2;
      value = (char*)realloc(value, init_len);
    }
    value[j++] = src[i++];
  }
  value[j] = '\0';
  Attribute* new = create_attribute(name, value);
  free(value);
  return new;
}

static TreeNode* parse_html(const char* str) {
    TreeNode* root = NULL;
    TreeNode* current_node = NULL;
    char buffer[1 << 16];
    int buffer_index = 0;
    
    while (*str != '\0') {
      if (*str == '<') {
        if(str[1] == '!') {
          // header skip
          skip_until(&str, ">");
          continue;
        }

        char* inside = read_until(&str, '>');
        size_t len = strlen(inside);
        // self close
        int is_self_close = check_self_close_tag(inside);

        if(inside[1] == '/') {
          /* --- CLOSE TAG --- */
          // get tag
          char tag_end[1 << 8];
          int i = 0;
          for(size_t j = 2; j < len; j++) {
            tag_end[i++] = inside[j];
          }
          tag_end[i] = '\0';
          inside[len] = '\0';
          // compare currently tag with this tag
          if(strcmp(tag_end, &inside[2]) != 0) {
            printf("parse_html: error miss math tag\n");
            exit(EXIT_FAILURE);
          }
          // get text to tag
          buffer[buffer_index] = '\0';
          remove_newlines(buffer);
          if (buffer[0] != '\0') {
              current_node->text = strdup(buffer);
          }
          buffer_index = 0;

          // update node
          current_node = current_node->parent;
        }else { 
          /* --- OPEN TAG --- */
          inside[len-1] = '\0';
          // check is skip tag
          if(is_skip_tag(&inside[1])) {
            char until[1 << 8];
            inside[strcspn(inside, " >")] = '\0';
            sprintf(until,"</%s>", &inside[1]);
            skip_until(&str,until);
            free(inside);
            continue;
          }

          char* token = read_until_with_quotes(inside,' ', buffer, 1 << 16);
          // update node
          TreeNode* new = create_tree_node(&buffer[1],NULL,current_node);
          if(current_node == NULL) { 
            root = new;
          } else {
            add_child(current_node, new);
          }
          current_node = new;

          // get attribute
          token = read_until_with_quotes(token, ' ', buffer, 1 << 16);
          remove_newlines(buffer);
          Attribute *head = NULL,*curr = NULL;
          while(buffer[0] != '\0') {
            Attribute* new = parse_attribute(buffer);
            if(new) {
              if(head) {
                curr->next = new; 
              } else {
                head = new;
              }
              curr = new;
            }
            token = read_until_with_quotes(token, ' ', buffer, 1 << 16);
          }
          new->attributes = head;

          // check for self closing tag
          if (is_self_close || is_self_closing_tag(current_node->tag_name)) {
              current_node = current_node->parent;
          }
        }
        free(inside);
        buffer_index = 0;
      }else {
        // Get text
        buffer[buffer_index++] = *str++;
      }
    }
    return root;
}

static TreeNode* find_tag(TreeNode* curr,const char* tag_name,const Attribute* attribute) {
  if(!curr) return NULL;

  /* CHECK */
  if(tag_name) {
    if(strcmp(curr->tag_name,tag_name) != 0) return NULL;
  }

  // count attribute should check
  int check_attribute = 0;
  if(attribute && attribute->name) check_attribute++;
  if(attribute && attribute->value) check_attribute++;

  if(!check_attribute) return curr; // only check tag name

  Attribute* it = curr->attributes;
  while(it) {
    int temp_count = 0;
    if(attribute && attribute->name && strcmp(attribute->name,it->name) == 0) temp_count++;
    if(attribute && attribute->value && strcmp(attribute->value,it->value) == 0) temp_count++;

    if(temp_count == check_attribute) return curr;

    it = it->next;
  }


  /* DIRECT */
  TreeNode* ret = NULL;
  ret = find_tag(curr->first_child,tag_name,attribute);
  if(ret) return ret;

  TreeNode* node_it = curr->next_sibling;
  while(node_it) {
    ret = find_tag(node_it,tag_name,attribute);
    if(ret) return ret;
    node_it = node_it->next_sibling;
  }

  return NULL;
}

static char* read_all_input(size_t *ret_length,FILE* stream) {
    size_t capacity = 1024;
    char* buffer = (char*)malloc(capacity);
    size_t length = 0;

    int ch;
    while ((ch = getc(stream)) != EOF) {
        if (length + 1 >= capacity) {
            capacity *= 2;
            buffer = (char*)realloc(buffer, capacity);
        }
        buffer[length++] = ch;
    }
    buffer[length] = '\0';
    if(ret_length) *ret_length = length;
    return buffer;
}


TreeNode* parse_to_tree(const char* file_path) {
  FILE* st = fopen(file_path,"r");
  if(!st) {
    printf("parse_to_tree: not found file on this path %s\n", file_path);
    return NULL;
  }
  char* html_content = read_all_input(NULL, st);
  TreeNode* root = parse_html(html_content);
  free(html_content);
  return root;
}

// int main() {
//     size_t lenght = 0;
//     char* html_content = read_all_input(&lenght);
//     printf("lenght input: %ld\n", lenght);
//     TreeNode* root = parse_html(html_content);

//     if (root) {
//       print_tree(root, 0);
//       printf("%25c", '-');
//       Attribute t = (Attribute){.name="class",.value="MainContent"};
//       TreeNode* find = find_tag(root,NULL, &t);
//       if(find) {
//         printf("Currently node is %s\nParent node is %s\n", find->tag_name, find->parent->tag_name);
//       } else {
//         printf("find tag not found\n");
//       }
//     } else {
//       printf("Failed to parse HTML.\n");
//     }
//     free_tree(root);
//     free(html_content);
//     return EXIT_SUCCESS;
// }