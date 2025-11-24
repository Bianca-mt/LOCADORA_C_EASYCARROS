# EASYCARROS 🚗💨

O EASYCARROS foi desenvolvido para digitalizar e otimizar os processos de locação de veículos. Ele reduz a papelada e o tempo gasto em cada transação, oferecendo uma experiência de usuário fluida tanto para a equipe administrativa quanto para os clientes.

**Objetivo:** Oferecer uma plataforma robusta e escalável para gerenciar todos os aspectos de uma operação de locação de veículos.

**Funcionalidades:**
**Login**: Necessário para autenticar os usuários, controlar o acesso para registrar atividades como de quem realizou tais ações no sistema;
**Cadastro e listagem de veiculos:** permitem o gerenciamento da frota; fornecem informações precisas dos veículos como: modelo, ano, placa e quilometragem;
**Area de alugel:** Onde o usuário poderá realizar a reserva do veiculo e demais informações;
**Devolução:** Registrar a devolução de um veiculo alugado pelo cliente.


Pré-requisitos
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

### Passos de Instalação (Frontend - React)

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

## 💻 Uso

Após a instalação, acesse `http://localhost:3000/` no seu navegador. O primeiro passo é criar um usuário administrador através do shell do Django.

**Exemplo de Funcionalidade:** Gerenciar a frota de veículos no painel de administração.
* Navegue até o menu "Area de cadastro".
* Clique em "Adicionar Novo Veículo".
* 

[Image of a screenshot of the main screen of the project]

* Preencha os dados (Modelo, Placa, Categoria, Valor da Diária, Status).

## 🧪 Executando Testes

Para garantir a qualidade do sistema, rode os testes unitários e de integração em ambas as aplicações.

**Backend (Django):**
```bash
cd backend
python manage.py test

Contato
Autor: Mário Figueiredo
Email: mariowsfigueiredo77@gmail.com
GitHub: mariowiiliam77
