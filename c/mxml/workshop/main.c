#include <stdio.h>

#include <mxml.h>

int main()
{
    FILE *fd=fopen("test.xml", "r");
    mxml_node_t *tree;

    tree = mxmlLoadFile(NULL, fd, MXML_TEXT_CALLBACK);
    
    fclose(fd);

    mxml_node_t *group_node=NULL;
    mxml_node_t *node=NULL;

    //group nodes
    for(group_node = mxmlFindElement(tree, tree, "group", NULL, NULL, MXML_DESCEND);
            group_node!=NULL;
            group_node = group_node->next) 
    {
        printf("<<<<<<<<<<<<<<<<<<<\n");
        for(node = group_node->child;
                node!=NULL && node != group_node->next;
                node = mxmlWalkNext(node, tree, MXML_DESCEND))
        {
            if(node->type != 0)
                continue;

            if(!strcmp(node->value.element.name, "name"))
                printf("name=%s, type=%d, text=%s\n", node->value.element.name, node->type, mxmlGetText(node, NULL));

            if(!strcmp(node->value.element.name, "tb_ip"))
                printf("name=%s, type=%d, text=%s\n", node->value.element.name, node->type, mxmlGetText(node, NULL));
        }

        printf("-------------\n");
    }

    return 0;
}
