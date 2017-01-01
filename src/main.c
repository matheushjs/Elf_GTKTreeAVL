#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <avltree.h>
#include <time.h>

#include <gtk/gtk.h>
#include <avl_app.h>

static
bool higher(const void *a, const void *b){
	return (*(int *)a > *(int *)b) ? true : false;
}

static
bool equal(const void *a, const void *b){
	return (*(int *)a == *(int *)b) ? true : false;
}

static
void print(const void *a, FILE *fp){
	fprintf(fp, "%d", *(int *)a);
}

static
void data_free(void *a){
	free(a);
}

static
gchar *read_full_file(FILE *fp){
	int size;
	gchar *ret;

	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	ret = (gchar *) malloc(sizeof(gchar) * (size+2));
	fread(ret, size, sizeof(gchar), fp);
	ret[size] = '\n';
	ret[size+1] = '\0';

	return ret;
}

static tree_t *global_tree;

gchar *insert_app_wrapper(const gchar *string){
	gchar *retval;
	void *key;

	key = malloc(sizeof(int));
	retval = (gchar *) malloc(sizeof(gchar) * 1000);
	if(sscanf(string, "%d", (int *) key) == 1){
		sprintf(retval, "Inserted %d\n", *(int *) key);
		tree_insert(global_tree, key);
	} else {
		sprintf(retval, "Invalid input\n");
		free(key);
	}

	return retval;
}

gchar *search_app_wrapper(const gchar *string){
	gchar *retval;
	void *key;

	key = malloc(sizeof(int));
	retval = (gchar *) malloc(sizeof(gchar) * 1000);

	if(sscanf(string, "%d", (int *) key) == 1){
		if(tree_search(global_tree, key))
			sprintf(retval, "Found %d\n", *(int *) key);
		else sprintf(retval, "Element %d is not in the tree\n", *(int *) key);
	} else sprintf(retval, "Invalid input\n");

	free(key);
	return retval;
}

gchar *remove_app_wrapper(const gchar *string){
	gchar *retval;
	void *key;

	key = malloc(sizeof(int));
	retval = (gchar *) malloc(sizeof(gchar) * 1000);

	if(sscanf(string, "%d", (int *) key) == 1){
		if(tree_remove(global_tree, key))
			sprintf(retval, "Removed %d\n", *(int *) key);
		else sprintf(retval, "Element %d is not in the tree\n", *(int *) key);
	} else sprintf(retval, "Invalid input\n");

	free(key);
	return retval;
}

gchar *successor_app_wrapper(const gchar *string){
	gchar *retval;
	void *key;
	void *succ;

	key = malloc(sizeof(int));
	retval = (gchar *) malloc(sizeof(gchar) * 1000);

	if(sscanf(string, "%d", (int *) key) == 1){
		succ = tree_successor(global_tree, key);
		if(succ)
			sprintf(retval, "Successor of %d: %d\n", *(int *) key, *(int *) succ);
		else sprintf(retval, "Error\n");
	} else sprintf(retval, "Invalid input\n");

	free(key);
	return retval;
}

gchar *predecessor_app_wrapper(const gchar *string){
	gchar *retval;
	void *key;
	void *pred;

	key = malloc(sizeof(int));
	retval = (gchar *) malloc(sizeof(gchar) * 1000);

	if(sscanf(string, "%d", (int *) key) == 1){
		pred = tree_predecessor(global_tree, key);
		if(pred)
			sprintf(retval, "Predecessor of %d: %d\n", *(int *) key, *(int *) pred);
		else sprintf(retval, "Error\n");
	} else sprintf(retval, "Invalid input\n");

	free(key);
	return retval;
}

gchar *max_app_wrapper(){
	gchar *retval;
	void *key;

	retval = (gchar *) malloc(sizeof(gchar) * 1000);
	key = tree_highest(global_tree);
	if(key) sprintf(retval, "Maximum: %d\n", *(int *) key);
	else sprintf(retval, "Tree is empty\n");

	return retval;
}

gchar *min_app_wrapper(){
	gchar *retval;
	void *key;

	retval = (gchar *) malloc(sizeof(gchar) * 1000);
	key = tree_lowest(global_tree);
	if(key) sprintf(retval, "Minimum: %d\n", *(int *) key);
	else sprintf(retval, "Tree is empty\n");

	return retval;
}

gchar *preorder_app_wrapper(){
	FILE *fp;
	gchar *ret;

	fp = tmpfile();
	tree_print_preorder(global_tree, fp);
	ret = read_full_file(fp);
	fclose(fp);

	return ret;
}

gchar *inorder_app_wrapper(){
	FILE *fp;
	gchar *ret;

	fp = tmpfile();
	tree_print_inorder(global_tree, fp);
	ret = read_full_file(fp);
	fclose(fp);

	return ret;
}

gchar *postorder_app_wrapper(){
	FILE *fp;
	gchar *ret;

	fp = tmpfile();
	tree_print_postorder(global_tree, fp);
	ret = read_full_file(fp);
	fclose(fp);

	return ret;
}

int main(int argc, char *argv[]){
	tree_t *tree;

	tree = tree_alloc(higher, equal, data_free, print);
	global_tree = tree;

	g_application_run(G_APPLICATION(avl_app_new()), argc, argv);

	tree_destroy(&tree);
	return 0;
}
