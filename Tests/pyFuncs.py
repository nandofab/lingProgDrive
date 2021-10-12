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
    service = conexaoDrive()    
    parents = [] 
    if(caminho.find('/') != -1):
        dados = buscaDados(caminhoDrive)
        pai = dados[-1]
        print(pai)
        if (pai=="1"):
            print( "Caminho de destino inexistente")
            return 1
        parents.append(pai['id'])
    file_metadata = {
        'name': nomePasta,
        'parents':parents,
        'mimeType': 'application/vnd.google-apps.folder'
    }
    file = service.files().create(body=file_metadata,fields='id').execute()
    
    print("Pasta " + nomePasta + " criada. Caminho: Meu Drive/ " + caminhoDrive)

def listarDrive():
    service = conexaoDrive()
    response = service.files().list().execute()
    for file in response.get('files', []):
            print(f"Name = {file.get('name')} ID = {file.get('id')}  Parents= {file.get('parents')}")


def buscaDados(caminho):
    try:
        service = conexaoDrive()                                            # inicia o serviço  
        listaCaminho = caminho.split("/")                                   # cria uma lista em que cada elemento da lista é uma pasta do caminho
        id_pai = 'root'                                                     # inicialmente o id pai é o root
        resultado = []                                                      # armazena todos os dados das pastas durante o caminho
        for nome in listaCaminho :                                          # para cada arquivo ou pasta do caminho
            response = service.files().list(                                # faz um request desse arquivo ou pasta dentro do escopo "My Drive"      
                    q = f"name='{nome}' and '{id_pai}' in parents",         # pelo nome e que tenha como pai o ultimo valor de id_pai
                    spaces='drive',
            ).execute()
            encontrado = response.get('files')[0]                           # recupera os dados do arquivo ou pasta encontrada      
            resultado.append(encontrado)                                    # O resultado consiste dos dados de todos os arquivos e pastas do caminho        
            id_pai = encontrado['id']                                       # atualiza o id_pai ao longo do caminho
           # print(encontrado)
        #print(resultado)
        return resultado # Retorna o resultado
    except IndexError:
        return None

def downloadArquivo(localizacao,destino):                       
    try:
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

        print("\nArquivo baixado com sucesso")
    except TypeError:
        print("Este caminho inexiste no drive")
    except FileNotFoundError:
        print("Destino inexistente")
    except :
        print("Nao eh possivel baixar pastas. Somente arquivos")


def upload(origem,destino):
    nomeArquivo = origem.split('/')[-1]
    service = conexaoDrive()    
    parents = []

    if(destino.find('/') == -1):
        if(destino != "MeuDrive"):
            dados = buscaDados(destino)
            pai = dados[-1]
            parents.append(pai['id'])        
    else:    
        dados = buscaDados(destino)
        pai = dados[-2]
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
        return "Upload feito com sucesso"
    
    except FileNotFoundError:  
        return "Caminho ou arquivo de origem inexistente."        
  
    except PermissionError:
        return "Permissao negada."

    except:
        return "Destino inexistente"


def moverArquivo(origem, destino):
    try:
        id_origem =[]
        service=conexaoDrive()
        dados_origem = buscaDados(origem)
        dados_origem= dados_origem[-1]
        id_origem.append(dados_origem['id'])
        id_origem = id_origem[0]
        #print(id_origem)
        id_destino =[]
        dados_destino = buscaDados(destino)
        dados_destino= dados_destino[-1]
        id_destino.append(dados_destino['id'])
        id_destino = id_destino[0]
        # print(id_destino)
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

  
        print ("Arquivo movido com sucesso")
    except TypeError:
        print("O arquivo de origem ou o local de destino nao existe")
    except:
        print("Erro desconhecido")





#def busca (nomePasta):
  #  service = conexaoDrive()
 #   page_token = None
   # 
   # temporario = nomePasta.split("/")
   # print(temporario)
    #nomePasta = temporario[len(temporario)-2]
   # print(nomePasta1)
    
    #while True:
   # response =   service.files().list(q= "mimeType='application/vnd.google-apps.folder' and name = '%s' " %(nomePasta),
    #                                                spaces='drive',
     #                                               fields='nextPageToken, files(id, name)',
      #                                              pageToken=page_token).execute()
    
        #print(response.get('files',[]))
   # if  (response.get('files',[]) ==[]):
 #           return None
    #    #if (response.get('files',[])) 
           # return "O arquivo " + nomePasta + " nao foi encontrado" 
  #  for file in response.get('files', []):
        
       # Process change
           # print ('Found file: %s (%s)' % (file.get('name'), file.get('id')))
   #     break
            #page_token = response.get('nextPageToken', None)
       
       #if page_token is None:
        #    break
   #     break 
#

  #  return file.get('id')



#def upload(origem, destino):
#    UPLOAD
 #   fmeiile_metadata = {'name': 'photo.jpg'}
 #   media = MediaFileUpload('photo.jpg', mimetype='image/jpeg')
 #   file = service.files().create(body=file_metadata,
 ##                                       media_body=media,
 #                                       fields='id').execute()


 #   return  "Upload feito com sucesso"
