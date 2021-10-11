from __future__ import print_function
from serviceHelper import Create_Service
import os.path
from googleapiclient.discovery import build
from google_auth_oauthlib.flow import InstalledAppFlow
from google.auth.transport.requests import Request
from google.oauth2.credentials import Credentials
from googleapiclient.http import MediaFileUpload



CLIENT_SECRET_FILE = 'danilo_secret.json'
API_NAME = 'drive'
API_VERSION = "v3"
SCOPES = ['https://www.googleapis.com/auth/drive'] 

# If modifying these scopes, delete the file token.json.
def criarPasta(nomePasta):
#    service = build('drive', 'v3', credentials=creds)
    contadorBarras = False
    service = Create_Service(CLIENT_SECRET_FILE,API_NAME,API_VERSION,SCOPES)
    nomeOriginal = nomePasta
    

    for i in range(len(nomePasta)): # Se o usuario inserir Pasta1/Pasta2, por exemplo, precisamos chamar a funcao busca para saber se Pasta1 existe
        if (nomePasta[i]=='/'):
             contadorBarras=True

    if (contadorBarras):            #Aqui chamamos a funcao busca caso seja encontrado um '/' no for acima
        id_pai =  busca(nomePasta)
        if (id_pai!=None):
            temporario = nomePasta.split("/")
            nomePasta = temporario[len(temporario)-1]
  
            file_metadata = {
                'name':  nomePasta,
                'parents': [id_pai],
                'mimeType': 'application/vnd.google-apps.folder'
            }
        else:
            return "O caminho especificado nao existe"

        file = service.files().create(body=file_metadata,
                                        fields='id').execute()
    
   
        #print('Folder ID: %s' % file.get('id'))





    if ( not contadorBarras):               # O usuario quer inserir na raiz. Exemplo:  pasta Teste1 apenas, e nao Teste1/Teste2
        file_metadata = {
            'name': nomePasta,
            'mimeType': 'application/vnd.google-apps.folder'
        }
        print("entrou")         
        file = service.files().create(body=file_metadata,
                                fields='id').execute()
 
  

    return "Pasta " + nomePasta + " criada. Caminho: " + nomeOriginal 


def busca (nomePasta):
    service = Create_Service(CLIENT_SECRET_FILE,API_NAME,API_VERSION,SCOPES)
    page_token = None
    
    temporario = nomePasta.split("/")
   # print(temporario)
    nomePasta = temporario[len(temporario)-2]
   # print(nomePasta1)
    
    while True:
        response =   service.files().list(q= "mimeType='application/vnd.google-apps.folder' and name = '%s' " %(nomePasta),
                                                    spaces='drive',
                                                    fields='nextPageToken, files(id, name)',
                                                    pageToken=page_token).execute()
    
        #print(response.get('files',[]))
        if  (response.get('files',[]) ==[]):
            return None
        #if (response.get('files',[])) 
           # return "O arquivo " + nomePasta + " nao foi encontrado" 
        for file in response.get('files', []):
        
       # Process change
           # print ('Found file: %s (%s)' % (file.get('name'), file.get('id')))
            break
            #page_token = response.get('nextPageToken', None)
       
       #if page_token is None:
        #    break
        break 


    return file.get('id')



#def upload(origem, destino):
#    UPLOAD
 #   fmeiile_metadata = {'name': 'photo.jpg'}
 #   media = MediaFileUpload('photo.jpg', mimetype='image/jpeg')
 #   file = service.files().create(body=file_metadata,
 #                                       media_body=media,
 #                                       fields='id').execute()


 #   return  "Upload feito com sucesso"



# https://developers.google.com/drive/api/v3/mime-types
# https://github.com/abhyamgupta123/Drive_Services_Project

#if __name__ == '__main__':
 #   main()

