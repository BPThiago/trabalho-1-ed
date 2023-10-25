# :briefcase: Trabalho 1 de Estrutura de Dados

## :gear: Como executar?

```shell
  git clone https://github.com/BPThiago/trabalho-1-ed.git
  
  # Abra o diretório recém criado
  cd trabalho-1-ed
  
  # Execute o script usando make
  make

  '''
     Ao executar o codigo:

     O usuário deve digitar e enviar make no terminal
     Escolher entre 0 e 1 
       sendo 0, o caminho padrao (imagem padrao)
       sendo 1, para inserir o caminho da imagem do computador do usuário

     O retorno previsto será um arquivo "convertido.ppm" contedo a imagem em tons de cinza
  '''
```

### :open_file_folder: Saida do programa: 
  A imagem modificada será armazenada no arquivo "convertido.ppm" no diretório: images/grayscale

## :camera: Screenshots

  ![image](https://github.com/BPThiago/trabalho-1-ed/assets/116036044/0a4b20d9-ac4f-4e55-b829-392766bd6f84) ![image](https://github.com/BPThiago/trabalho-1-ed/assets/116036044/c74838bf-f0b2-4438-a786-76365b68f6e3)


## :computer: Decisões de Implementação 

### Em image.c

    struct image -> Foi decidida uma abordagem vetorial da matriz, para facilitar a manipulação de imagem, na visão do grupo 
     - Foram implementadas funções no header a parte como: 
        1) get_image_width
        2) get_image_heith
     Para capturar a quantidade de colunas e linhas da imagem, para que usuario consiga acessar esses atributos de modo mais abstraido 
