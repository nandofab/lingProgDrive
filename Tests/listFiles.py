from serviceHelper import Create_Service

CLIENT_SECRET_FILE = 'client_secret.json'
API_NAME = 'drive'
API_VERSION = "v3"
SCOPES = ["https://www.googleapis.com/auth/drive"] 

service = Create_Service(CLIENT_SECRET_FILE,API_NAME,API_VERSION,SCOPES)


response = service.files().list(fields='name').execute()
print(response)