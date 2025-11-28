# EASYCARROS 🚗💨

![GitHub repo size](https://img.shields.io/github/repo-size/iuricode/README-template?style=for-the-badge)
![GitHub language count](https://img.shields.io/github/languages/count/iuricode/README-template?style=for-the-badge)
![GitHub forks](https://img.shields.io/github/forks/iuricode/README-template?style=for-the-badge)
![Bitbucket open issues](https://img.shields.io/bitbucket/issues/iuricode/README-template?style=for-the-badge)
![Bitbucket open pull requests](https://img.shields.io/bitbucket/pr-raw/iuricode/README-template?style=for-the-badge)


O EASYCARROS foi desenvolvido para digitalizar e otimizar os processos de locação de veículos. Ele reduz a papelada e o tempo gasto em cada transação, oferecendo uma experiência de usuário fluida tanto para a equipe administrativa quanto para os clientes.

**Objetivo:**

Oferecer uma plataforma robusta e escalável para gerenciar todos os aspectos de uma operação de locação de veículos.

**Funcionalidades:**

**Login**: Necessário para autenticar os usuários, controlar o acesso para registrar atividades como de quem realizou tais ações no sistema;

**Cadastro e listagem de veiculos:** permitem o gerenciamento da frota; fornecem informações precisas dos veículos como: modelo, ano, placa e quilometragem;

**Area de alugel:** Onde o usuário poderá realizar a reserva do veiculo e demais informações;

**Devolução:** Registrar a devolução de um veiculo alugado pelo cliente.


## 💻 Pré-requisitos

Antes de começar, certifique-se de ter instalado:

Para rodar o projeto localmente, você precisará ter instalado:

* Node.js (v18+) e npm
* Python (v3.10+) e pip
* PostgreSQL (ou Docker para um ambiente conteinerizado)

### Passos de Instalação (Backend - Django)

1.  **Clone o repositório e navegue para o diretório backend:**
    ```bash
    git clone [https://github.com/](https://github.com/Bianca-mt/LOCADORA_C_EASYCARROS.git)
    cd LOCADORA_C_EASYCARROS/backend
    ```

2.  **Crie e ative o ambiente virtual e instale as dependências:**
    ```bash
    python -m venv venv
    source venv/bin/activate  # ou venv\Scripts\activate no Windows
    pip install -r requirements.txt
    ```

3.  **Configuração do Banco de Dados:**
    Crie o arquivo `.env` baseado no `.env.example` e configure as credenciais do seu PostgreSQL.
    ```bash
    cp .env.example .env
    # Edite o arquivo .env com suas credenciais de DB
    ```

4.  **Execute as migrações do banco de dados:**
    ```bash
    python manage.py makemigrations
    python manage.py migrate
    ```

5.  **Execute o servidor Django:**
    ```bash
    python manage.py runserver
    # A API estará rodando em [http://127.0.0.1:8000/](http://127.0.0.1:8000/)
    ```

### Passos de Instalação (Frontend)

1.  **Navegue para o diretório frontend e instale as dependências:**
    ```bash
    cd ../frontend
    npm install
    ```

2.  **Execute a aplicação React:**
    ```bash
    npm start
    # A interface estará rodando em http://localhost:3000/
    ```

## ☕ Usando EASYCARROS

Após a instalação, acesse `http://localhost:3000/` no seu navegador. O primeiro passo é criar um usuário administrador através do shell do Django.



**Exemplo de Funcionalidade:** Gerenciar a frota de veículos no painel de administração.
* Navegue até o menu "Area de cadastro".
* Clique em "Adicionar Novo Veículo".
* 

[Image of a screenshot of the main screen of the project]

* Preencha os dados (Modelo, Placa, Categoria, Valor da Diária, Status).
  *

  ## 📫 Contribuindo para o EASYCARROS

Para contribuir com <nome_do_projeto>, siga estas etapas:

1. Bifurque este repositório.
2. Crie um branch: `git checkout -b <nome_branch>`.
3. Faça suas alterações e confirme-as: `git commit -m '<mensagem_commit>'`
4. Envie para o branch original: `git push origin <nome_do_projeto> / <local>`
5. Crie a solicitação de pull.

Como alternativa, consulte a documentação do GitHub em [como criar uma solicitação pull](https://help.github.com/en/github/collaborating-with-issues-and-pull-requests/creating-a-pull-request).


## 🧪 Executando Testes

Para garantir a qualidade do sistema, rode os testes unitários e de integração em ambas as aplicações.

**Backend (Django):**
```bash
cd backend
python manage.py
 ```


## Contato:

Autor: Mário Figueiredo

Email: mariowsfigueiredo77@gmail.com

Github: mariowilliam77


