#include "minishell.h"
#include "builtins.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*ret;

	ret = malloc(sizeof(t_list));
	if (ret == NULL)
		return (ret);
	ret->content = content;
	ret->next = NULL;
	return (ret);
}

t_env   create_key_value(char *env)
{
    t_env   key_value;
    int     lkey;
    int     aux;

    lkey = 0;
    aux = 0;
    while(env[lkey] && env[lkey] != '=')
        lkey ++;
    key_value.key = ft_calloc(lkey, sizeof(char));
    if(ft_calloc == NULL)
        perror("fallo de malloc key");
    while(lkey--)
        key_value.key[aux] = env[aux++];
    env += aux;
    key_value.value = ft_calloc(ft_strlen(env), sizeof(char));
    while(*env)
        key_value.value



}

int ft_create_env_list(char **env)
{
    int counter;
    while(env[counter])
       ft_lstnew(create_key_value(env[counter++]));
}