from __future__ import print_function
from tqdm import tqdm
import os
import io
from googleapiclient.discovery import build
from google_auth_oauthlib.flow import InstalledAppFlow
from google.auth.transport.requests import Request
from google.oauth2.credentials import Credentials
from googleapiclient.http import MediaFileUpload, MediaIoBaseDownload
from time import sleep
import sys

CLIENT_SECRET_FILE = 'credentials.json'
API_NAME = 'drive'
API_VERSION = "v3"
SCOPES = ['https://www.googleapis.com/auth/drive'] 

def conexaoDrive():
    creds = None
    # O arquivo token.json armazena o acesso do usário e os refresh tokens, 
    # é criado automaticamente quando a autoriazação é concedida pela primeira vez
    if os.path.exists('token.json'):
        creds = Credentials.from_authorized_user_file('token.json', SCOPES)
    # Se não tiver autorização do usuário, pede.
    if not creds or not creds.valid:
        if creds and creds.expired and creds.refresh_token:
            creds.refresh(Request())
        else:
            flow = InstalledAppFlow.from_client_secrets_file(CLIENT_SECRET_FILE, SCOPES)
            creds = flow.run_local_server(port=0)
        # Salva a autorização
        with open('token.json', 'w') as token:
            token.write(creds.to_json())
    service = build(API_NAME, API_VERSION , credentials=creds)
    return service 


def criarPasta(caminho):
    caminhoDrive,lixo,nomePasta = caminho.rpartition('/')       
    parents = [] 
    try:
        service = conexaoDrive() 
        if(caminho.find('/') != -1):
            dados = buscaDados(caminhoDrive)
            pai = dados[-1]
            parents.append(pai['id'])
        
        file_metadata = {
            'name': nomePasta,
            'parents':parents,
            'mimeType': 'application/vnd.google-apps.folder'
        }
        service.files().create(body=file_metadata,fields='id').execute()
        
        return "Pasta " + nomePasta + " criada com sucesso! Caminho: /" + caminhoDrive
    except:
        return "***** Erro: A pasta onde você deseja criar uma nova ainda não existe *****" 

def listarDrive(caminho):
    try:
        service = conexaoDrive()
        id_pai = ''
        if (caminho == 'MeuDrive'):
            id_pai = 'root'
        else:
            dados = buscaDados(caminho)        
            if dados[-1]['mimeType'] != 'application/vnd.google-apps.folder':
                raise TypeError
            id_pai = dados[-1]['id']
        request = service.files().list(q=f"'{id_pai}' in parents and trashed = false").execute()
        arquivos = request.get('files')
        nextPageToken = request.get('nextPageToken')
        while nextPageToken:                                            # se o request foi didivido em páginas
            request = service.files().list(                                
                q = f"'{id_pai}' in parents",
                pageToken = nextPageToken
            ).execute()
            arquivos.extend(request.get('files'))                       # extende o resultado do request
            nextPageToken = request.get('nextPageToken')                # verifica se tem outra pagina       
        print('%-70s %s' %('          ***** Nome *****','          ***** Id *****'))
        for arquivo in arquivos:
            print('%-70s %s' %(arquivo['name'],arquivo['id']))
    except TypeError:
        print( "***** Erro: caminho não se refere a uma pasta *****")

def buscaDados(caminho):
    try:
        service = conexaoDrive()                                            # inicia o serviço  
        listaCaminho = caminho.split("/")                                   # cria uma lista em que cada elemento da lista é uma pasta do caminho
        id_pai = 'root'                                                     # inicialmente o id pai é o root
        resultado = []                                                      # armazena todos os dados das pastas durante o caminho
        for nome in listaCaminho :                                          # para cada arquivo ou pasta do caminho
            request = service.files().list(                                 # faz um request desse arquivo ou pasta dentro do escopo "My Drive"      
                    q = f"name='{nome}' and '{id_pai}' in parents",         # pelo nome e que tenha como pai o ultimo valor de id_pai
                    spaces='drive',
            ).execute()
            if(request.get('files')== []):
                raise(TypeError)
            arquivos = request.get('files')
            nextPageToken = request.get('nextPageToken')
            while nextPageToken:                                            # se o request foi didivido em páginas
                request = service.files().list(                             # faz um request desse arquivo ou pasta dentro do escopo "My Drive"      
                    q = f"name='{nome}' and '{id_pai}' in parents",         # pelo nome e que tenha como pai o ultimo valor de id_pai
                    spaces='drive',
                    pageToken = nextPageToken
                ).execute()
                arquivos.extend(request.get('files'))                       # extende o resultado do request
                nextPageToken = request.get('nextPageToken')                # verifica se tem outra pagina
            encontrado = arquivos[0]                                        # recupera os dados do arquivo ou pasta encontrada      
            resultado.append(encontrado)                                    # O resultado consiste dos dados de todos os arquivos e pastas do caminho        
            id_pai = encontrado['id']                                       # atualiza o id_pai ao longo do caminho
        return resultado                                                    # Retorna o resultado
    except TypeError:
        print( "***** Erro: Este caminho inexiste no drive *****")
        sys.exit()

def downloadArquivo(localizacao,destino):                       
    try:
        if not os.path.exists(destino):
            raise(FileNotFoundError)

        service = conexaoDrive()
        dados = buscaDados(localizacao)                                     # Busca os dados dos arquivos ao longo da localização no drive              
        arquivo = dados[-1]                                                 # o arquivo que se deseja baixar é o ultimo dos dados
      
        request = service.files().get_media(fileId=arquivo['id'])           # faz um request pra pegar a mídia do dado
        fh = io.BytesIO()
        downloader = MediaIoBaseDownload(fd=fh,request=request)             # prepara o downloader
        terminou = False
        progresso = tqdm(total=100)                                         # configura a barra de download
     
        while not terminou:
            status,terminou = downloader.next_chunk()                       # baixa o próximo pedaço
            progresso.update(status.progress() * 100)                       # atualiza a barra de download

        fh.seek(0)
        with open(os.path.join(destino,arquivo['name']),'wb') as arquivo:   # cria o arquivo com o nome escolhido no destino desejado e preenche ele com o binário baixado
            arquivo.write(fh.read())
            arquivo.close() 
        return "Download feito com sucesso"
    except TypeError:
        return "***** Erro: A origem inexiste no drive *****"
    except FileNotFoundError:
        return  "***** Erro: Destino inexistente *****"
    except :
        return  "***** Erro: Nao eh possivel baixar pastas,somente arquivos *****"


def uploadArquivo(origem,destino):
    if not os.path.exists(origem):
            raise(FileNotFoundError)
    nomeArquivo = origem.split('/')[-1]
    service = conexaoDrive()    
    parents = []
    
    if(destino != "MeuDrive"):
        dados = buscaDados(destino)
        pai = dados[-1]
        parents.append(pai['id'])        
     
    try:
        service = conexaoDrive()    
        file_metadata = {
            'name': nomeArquivo,
            'parents': parents
        }                                                       # MIME TYPES: https://developers.google.com/drive/api/v3/ref-export-formats
        media = MediaFileUpload(origem, mimetype='*/*')         # '*/*' => significa q qualquer tipo eh aceito. Há infinitos mime types...
        file = service.files().create(
            body=file_metadata,       
            media_body=media,
            fields='id'
        ).execute()
        return  "Upload feito com sucesso"
    
    except PermissionError:
        return "***** Erro: Permissao negada. *****"
    except:
        return "***** Erro: Destino inexistente *****"


def moverArquivo(origem, destino):
    try:
        id_origem =[]
        service=conexaoDrive()
        dados_origem = buscaDados(origem)
        if (dados_origem == None):
            raise(TypeError)  
        dados_origem= dados_origem[-1]
        id_origem.append(dados_origem['id'])
        id_origem = id_origem[0]
        #print(id_origem)
        id_destino =[]
        dados_destino = buscaDados(destino)
        if (dados_destino == None):
            raise(TypeError)  
        dados_destino= dados_destino[-1]
        id_destino.append(dados_destino['id'])
        id_destino = id_destino[0]

        # Retrieve the existing parents to remove
        file = service.files().get(fileId=id_origem,
                                     fields='parents').execute()
        previous_parents = ",".join(file.get('parents'))
        #Move the file to the new folder
        file = service.files().update(fileId=id_origem,
                                addParents=id_destino,
                                removeParents=previous_parents,
                                fields='id, parents').execute()
 
        for i in range(21):
            sys.stdout.write('\r')
            sys.stdout.write("[%-20s] %d%%" % ('='*i, 5*i))
            sys.stdout.flush()
            sleep(0.25)  
        return "\nArquivo movido com sucesso"      
   
    except TypeError:
        return "***** Erro:O arquivo de origem ou o local de destino nao existe ***** "
    except:
        return "***** Erro desconhecido ***** "
