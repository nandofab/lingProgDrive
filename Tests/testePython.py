from __future__ import print_function
import os.path
from googleapiclient.discovery import build
from google_auth_oauthlib.flow import InstalledAppFlow
from google.auth.transport.requests import Request
from google.oauth2.credentials import Credentials
from googleapiclient.http import MediaFileUpload
import shutil
from os.path import join
# If modifying these scopes, delete the file token.json.
def conexaoDrive():
    SCOPES = ['https://www.googleapis.com/auth/drive']
    creds = None
    # The file token.json stores the user's access and refresh tokens, and is
    # created automatically when the authorization flow completes for the first
    # time.
    if os.path.exists('token.json'):
        creds = Credentials.from_authorized_user_file('token.json', SCOPES)
    # If there are no (valid) credentials available, let the user log in.
    if not creds or not creds.valid:
        if creds and creds.expired and creds.refresh_token:
            creds.refresh(Request())
        else:
            flow = InstalledAppFlow.from_client_secrets_file(
                'client_secret_248993973959-pfaq6d7i5pkuejj77usmpbsvs6nl9p4e.apps.googleusercontent.com.json', SCOPES)
            creds = flow.run_local_server(port=0)
        # Save the credentials for the next run
        with open('token.json', 'w') as token:
            token.write(creds.to_json())

    service = build('drive', 'v3', credentials=creds)
    return service 


def criarPasta(nomePasta):
#    service = build('drive', 'v3', credentials=creds)
    contadorBarras = False
    service = conexaoDrive() 
    nomeOriginal = nomePasta
   
   # jaExiste = busca(nomePasta)
   # if (jaExiste !=None)
    testeDuplicado = nomePasta + '/'
  #  print(testeDuplicado)
    for i in range(len(nomePasta)): # Se o usuario inserir Pasta1/Pasta2, por exemplo, precisamos chamar a funcao busca para saber se Pasta1 existe
        if (nomePasta[i]=='/'):
             contadorBarras=True

    if (contadorBarras):            #Aqui chamamos a funcao busca caso seja encontrado um '/' no for acima
        id_pai =  busca(nomePasta)
        if (id_pai!=None):        # Se o caminho existe..
            idChecagemDuplicado = busca(testeDuplicado)
            
    #        print(idChecagemDuplicado)
            if (idChecagemDuplicado==None):

                temporario = nomePasta.split("/")
                nomePasta = temporario[len(temporario)-1]
  
                file_metadata = {
                    'name':  nomePasta,
                    'parents': [id_pai],
                    'mimeType': 'application/vnd.google-apps.folder'
                }
            else:
                return "Esta pasta ja existe"
       

        else:
            return "O caminho especificado nao existe"

        file = service.files().create(body=file_metadata,
                                        fields='id').execute()
    
   
        #print('Folder ID: %s' % file.get('id'))





    if ( not contadorBarras):               # O usuario quer inserir na raiz. Exemplo:  pasta Teste1 apenas, e nao Teste1/Teste2
        idChecagemDuplicado = busca(testeDuplicado)
        if (idChecagemDuplicado ==None):
            file_metadata = {
                'name': nomePasta,
                'mimeType': 'application/vnd.google-apps.folder'
             }
            print("entrou")
         
            file = service.files().create(body=file_metadata,
                                fields='id').execute()
        else:
            return "Pasta duplicada"
  

    return "Pasta " + nomePasta + " criada. Caminho: " + nomeOriginal 


def busca (nomePasta):
    service = conexaoDrive()
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



def upload(origem,destino):
 #  UPLOAD
   # source = join('C', 'Users', 'nando', 'AppData', 'Local', 'Packages','CanonicalGroupLimited.Ubuntu20.04onWindows_79rhkp1fndgsc','LocalState','rootfs','home','nandofab2011','Nando','TrabalhoDupla','photo.jpg')
    #destination = join('C', 'Users', 'nando', 'AppData', 'Local', 'Packages','CanonicalGroupLimited.Ubuntu20.04onWindows_79rhkp1fndgsc','LocalState','rootfs','home','nandofab2011','Nando','TrabalhoDupla','tentativa2','photo2.jpg')
    
  #
   # origem = '/home/nandofab2011/Nando/TrabalhoDupla/tentativa2/photo.jpg'
    #destino = '/home/nandofab2011/Nando/TrabalhoDupla/tentativa2/Tests/photo2.jpg'
    
   # print(origem)
    #shutil.move(source, destination)
    ultimoOrigem = origem.split("/")                   # ultimoOrigem é um vetor com nomes entre '/'. Exemplo: teste1/teste2/teste.jpg=> ultimoOrigem = [teste1, teste 2, teste3.jpg]
    arquivoOrigem = ultimoOrigem[len(ultimoOrigem)-1] #arquivo origem, no exemplo do comentário de cima, seria o teste3.jpg
    
    #shutil.copyfile(origem, './%s' % arquivoOrigem) # Aqui copia-se o arquivo da origem para a pasta atual onde o programa está rodando
    

    try:
        shutil.copyfile(origem, './%s' % arquivoOrigem) # Aqui copia-se o arquivo da origem para a pasta atual onde o programa está rodando
    
       # shutil.copy(source, destination)
        #print("File copied successfully.")
       


        destino = destino +'/' + arquivoOrigem # inserimos o arquivo no destino para que  a funcao busca funcione adequadamente
     
        #print(destino)
    
        id_pai = busca(destino)# Se o usuario inserir "Teste1/Teste2/Teste3/foto.jpg", pegaremos o id de Teste3 

        if (id_pai!=None):
            nomeArquivo = arquivoOrigem
            service = conexaoDrive()    
            file_metadata = {'name': nomeArquivo,
                 'parents': [id_pai]
                }  

            media = MediaFileUpload(nomeArquivo, mimetype='*/*')   # MIME TYPES: https://developers.google.com/drive/api/v3/ref-export-formats
            file = service.files().create(body=file_metadata,       # '*/*' => significa q qualquer tipo eh aceito. Há infinitos mime types...
                                            media_body=media,
                                            fields='id').execute()
            return "Upload feito com sucesso"

        #else:
         #   raise Exception ("Destino inexistente")

        
        
    except FileNotFoundError:
        
        return "Caminho ou arquivo de origem inexistente."
         
        
    except PermissionError:
        return "Permissao negada."
         
        
    except:
        #if (id_pai==None):
            #print(id_pai)
        return "Destino inexistente"
            #print(id_pai)
       #return "Erro desconhecido"






# https://developers.google.com/drive/api/v3/mime-types
# https://github.com/abhyamgupta123/Drive_Services_Project

#if __name__ == '__main__':
 #   main()

