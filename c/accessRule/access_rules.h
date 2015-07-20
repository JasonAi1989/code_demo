#ifndef _ACCESS_RULES_H
#define _ACCESS_RULES_H

//access rule
struct ac_rule
{
	char	enable;	//1 enable, 0 disable
	int 	dst_addr;
	int 	src_addr;
	short 	dst_port;
	short 	src_port;
};

struct ac_rule_list
{
	struct ac_rule_list *next,*prev;
	struct ac_rule		*rule;
};

void add_ac_rule(struct ac_rule_list** head, struct ac_rule* data);
void del_ac_rule(struct ac_rule_list** head, unsigned int index);
void destroy_rule_list(struct ac_rule_list** head);

int  get_local_rules(struct ac_rule_list** head);
	
#endif