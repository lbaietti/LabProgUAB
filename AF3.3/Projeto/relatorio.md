# Relatorio

O sistema foi dividido em quatro módulos com responsabilidades distintas. O módulo validacao foi mantido separado de contacto porque as suas funções têm utilidade independente e podem ser reutilizadas por outros módulos ou projetos futuros sem arrastar a definição de Contacto. Se estivessem dentro de contacto.c, qualquer módulo que quisesse validar um email sem criar um contacto teria de incluir toda a estrutura, criando acoplamento desnecessário. Esta decisão segue o princípio de baixo acoplamento do RF 3.2 e o critério de alta coesão do RF 3.1.

O baixo acoplamento foi garantido de duas formas: as variáveis de estado (contactos[] e total em lista.c) são declaradas como static, tornando-as invisíveis ao exterior; e todos os módulos acedem à estrutura Contacto apenas através do tipo público definido em contacto.h, nunca manipulando os seus campos diretamente fora do módulo contacto. A função lista_obterTodos resolve de forma limpa o problema de expor os dados da lista para o módulo io sem quebrar o encapsulamento; copia os contactos para um buffer externo fornecido pelo chamador, mantendo o array interno completamente opaco.

