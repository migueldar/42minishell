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

t_env  *create_key_value(char *env, t_env *old)
{
    t_env   *key_value;
    int     lkey;
    int     aux;
    lkey = 0;
    aux = 0;
    key_value = malloc(sizeof(t_env *));
    while(env[lkey] && env[lkey] != '=')
        lkey ++;
    key_value->key = ft_calloc(sizeof(char), (lkey +1));
    if(key_value->key == NULL)
        perror("fallo de malloc key");
    while(lkey--)
    {
        key_value->key[aux] = env[aux];
        aux ++;
    }
    env += aux;
    aux = 0;
    key_value->value = ft_calloc(ft_strlen(env), sizeof(char));
    if(key_value->key == NULL)
        perror("fallo de malloc value");
    while(env[aux])
    {
        key_value->value[aux] = env[aux];
        aux ++;
    }    
    key_value->next = NULL; 
    if(old)
        old->next = key_value;
    return(key_value);
}


int ft_create_env_list(char **env)
{
    int counter;
    t_env  *envi;
    t_env *old;
    t_env *aux;

    counter = 0;
    envi = create_key_value(env[counter], NULL);
    aux = envi;
    counter ++;
    while(env[counter])
    {
        old = create_key_value(env[counter], aux);
        aux = old;
        counter ++;
    }
    return(0);
}