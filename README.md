# Mini(s)hell !
![norminette](https://github.com/42Lausanne-fltorren/Minishell/actions/workflows/main.yml/badge.svg) ![](https://github.com/42Lausanne-fltorren/Minishell/blob/gh-pages/minishell_percentage.svg)
## Introduction
Le but de ce projet est de créer un shell minimaliste en C.
Nous allons commencer par créer un lexer qui va transformer une ligne de commande en une liste de tokens.

Ensuite, nous allons créer un parser qui va transformer cette liste de tokens en une liste de commandes.

Enfin, nous allons créer un expander qui va transformer les variables en leur valeur.

Enfin, nous allons créer un exécuteur qui va exécuter ces commandes.

## Lexer
Notre lexer doit être capable de reconnaître les tokens suivants:
- Les singlequotes (') et les doublequotes (")
	- Le contenu des singlequotes désactivent l'interprétation des caractères spéciaux est est de type `string`
	- Le contenu des doublequotes active l'interprétation des caractères spéciaux sauf les variables ($) et est de type `word`
- Les redirections : "<", ">", ">>", "<<"
	- "<" est un token de type `in`
	- ">" est un token de type `out`
	- ">>" est un token de type `append`
	- "<<" est un token de type `heredoc`
- Les pipes: "|" (type `pipe`)
- Everything else is a token of type `word`

### Structure des tokens
```C
typedef enum e_token_type
{
	WORD,
	STRING,
	IN,
	OUT,
	APPEND,
	HEREDOC,
	PIPE
} t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
} t_token;

```

### Exemples
```bash
echo "Hello, $NAME !" > file.txt
```
Le lexer doit retourner la liste suivante:
```python
[
	('word', 'echo'),
	('word', 'Hello, $NAME !'),
	('out', '>')
	('word', 'file.txt')
]
```

```bash
< file.txt grep 'Hello world' | wc -l > count.txt
```
Le lexer doit retourner la liste suivante:
```python
[
	('in', '<'),
	('word', 'file.txt'),
	('word', 'grep'),
	('string', 'Hello world'),
	('pipe', '|'),
	('word', 'wc'),
	('word', '-l'),
	('out', '>'),
	('word', 'count.txt')
]
```

## Parser
Notre parser doit être capable de transformer la liste de tokens en une liste de commandes.
Une commande est une liste de tokens séparée par des pipes.

### Les règles
- Si un token est de type `in`, le token suivant doit être de type `word` ou `string`, et représente le fichier d'entrée.
- Si un token est de type `out` ou `append`, le token suivant doit être de type `word` ou `string`, et représente le fichier de sortie.
- Si un token est de type `heredoc`, le token suivant doit être de type `word` ou `string`, et représente la string de fin.
- Si un token est de type `pipe`, le token suivant doit être de type `word` ou `string`, et représente la commande suivante. Et le token précédent doit être de type `word` ou `string`.
- Si un token est de type `word` ou `string`, il peut être suivi par un nombre quelconque de tokens de type `word` ou `string`. Le premier token est la commande, les suivants sont les arguments.

### Structure des commandes
```C
typedef struct s_command
{
	t_token *in;
	t_token	*cmd;
	t_token	**args; // NULL terminated array
	t_token	*out;
} t_command;
```

### Exemples
```bash
echo "Hello, $NAME !" > file.txt
```
```python
[
	('word', 'echo'),
	('word', 'Hello, $NAME !'),
	('out', '>')
	('word', 'file.txt')
]
```
Le parser doit retourner la liste suivante:
```python
[
	{
		'in': NULL,
		'cmd': ('word', 'echo'),
		'args': [('word', 'Hello, $NAME !')],
		'out': ('out', 'file.txt')
	}
]
```

```bash
< file.txt grep 'Hello world' | wc -l > count.txt
```
```python
[
	('in', '<'),
	('word', 'file.txt'),
	('word', 'grep'),
	('string', 'Hello world'),
	('pipe', '|'),
	('word', 'wc'),
	('word', '-l'),
	('out', '>'),
	('word', 'count.txt')
]
```
Le parser doit retourner la liste suivante:
```python
[
	{
		'in': ('in', 'file.txt'),
		'cmd': ('word', 'grep'),
		'args': [('string', 'Hello world'), NULL],
		'out': NULL
	},
	{
		'in': NULL,
		'cmd': ('word', 'wc'),
		'args': [('word', '-l'), NULL],
		'out': ('out', 'count.txt')
	}
]
```

## Expander
Notre expander doit être capable de transformer les variables en leur valeur. Les variables sont de la forme `$NAME` et sont remplacées par leur valeur dans l'environnement (`envp`).
Les seuls tokens qui peuvent contenir des variables sont de type `word`.

### Procédure
On cherche dans chaque token de type `word` si il contient une variable.
Si c'est le cas, on trouve la position du "$" (`i`), puis on trouve la longueur de la variable (`len`).
On crée un substring de `0` à `i`, et un de `(i + len)` à la fin.
On cherche la valeur de la variable dans l'environnement et on concatène les trois substrings.

### Pseudo-code
```C
for each token in tokens
	if token.type == WORD
		i = find_char(token.value, '$')
		if i != -1
			len = find_len(token.value, i)
			substr1 = substr(token.value, 0, i)
			substr2 = substr(token.value, i + len, len(token.value))
			value = get_env(envp, substr2)
			token.value = concat(substr1, value, substr2)
```

## Exécuteur
Notre exécuteur doit être capable d'exécuter les commandes.
Pour chaque commande, on crée un processus fils avec `fork()`, et on exécute la commande avec `execve()`.

En entrée:
- Si il y a une redirection d'entrée, on redirige l'entrée vers le fichier de redirection.
- Si la commande est la première on redirige pas l'entrée (`stdin`).
- Sinon on redirige l'entrée vers le pipe.

En sortie:
- Si il y a une redirection de sortie, on redirige la sortie vers le fichier de redirection.
- Si la commande est la dernière on redirige pas la sortie (`stdout`).
- Sinon on redirige la sortie vers le pipe.

Pour la commande:
- On cherche dans le `PATH` l'exécutable.
- Si on le trouve, on l'exécute avec les arguments.
- Sinon, on affiche un message d'erreur.
