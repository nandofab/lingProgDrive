from __future__ import print_function
import os.path
from googleapiclient.discovery import build
from google_auth_oauthlib.flow import InstalledAppFlow
from google.auth.transport.requests import Request
from google.oauth2.credentials import Credentials
from googleapiclient.http import MediaFileUpload

# If modifying these scopes, delete the file token.json.
SCOPES = ['https://www.googleapis.com/auth/drive']

def criarPasta(nomePasta):
    """Shows basic usage of the Drive v3 API.
    Prints the names and ids of the first 10 files the user has access to.
    """
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
                'credentials.json', SCOPES)
            creds = flow.run_local_server(port=0)
        # Save the credentials for the next run
        with open('token.json', 'w') as token:
            token.write(creds.to_json())

    service = build('drive', 'v3', credentials=creds)
# CRIACAO DE PASTA
    # Call the Drive v3 API
    #def create_folder_in_folder(folder_name, parent_folder_id):
    file_metadata = {
        'name': nomePasta,
        'mimeType': 'application/vnd.google-apps.folder'
    }
    file = service.files().create(body=file_metadata,
                                fields='id').execute()
    folder_id = file.get('id')
   # print('Folder ID: %s' % file.get('id'))

    file_metadata = {
        'name':  'pastaInterior',
        'parents': [folder_id],
        'mimeType': 'application/vnd.google-apps.folder'
    }

    file = service.files().create(body=file_metadata,
                                        fields='id').execute()

    print('Folder ID: %s' % file.get('id'))

#    UPLOAD
    file_metadata = {'name': 'photo.jpg'}
    media = MediaFileUpload('photo.jpg', mimetype='image/jpeg')
    file = service.files().create(body=file_metadata,
                                        media_body=media,
                                        fields='id').execute()


    return "Pasta " + nomePasta + " criada"



# https://developers.google.com/drive/api/v3/mime-types
# https://github.com/abhyamgupta123/Drive_Services_Project

#if __name__ == '__main__':
 #   main()

