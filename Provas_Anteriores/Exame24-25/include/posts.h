#ifndef POSTS_H
#define POSTS_H



/**
* @brief Representa um post gerido pelo sistema
*
* A estrutura é exposta no cabeçalho para permitir leitura em testes e 
* integrar de forma controlada com outros módulos, sem expor o armazenamento interno do array.
 */

typedef struct {
    char descricao[100];
    char nome[30];
    char nicho[30];
}Post;


/**
* @brief Gerir os dados de forma dinâmica, de modo a incluir a adição, remoção e edição dos posts
* @todo Estes dados terão de posteriormente ser carregados em ficheiro csv com lista ordenada.
*/

int adicionar_post(const char* descricao, const char* nome, const char* nicho);

int editar_post(const char* descricao, int fotos[]);

/**
* @brief remove por completo todo o conteúdo do post.
 */

int remover_posts(void);





#endif  