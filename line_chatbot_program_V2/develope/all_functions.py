import os

from element_picker import ElementPicker
from learning_bot_v3 import LearningBot


def show_commands():
    reply_msg = (
"\
#指令:\n\
- 抽(或 pick)\n\
- 學習(或 learn)\n\
- 開頭空一格 = 對話模式\n\
  會回答學習過的東西\n\n\
使用 '#指令 help' 來查詢完整指令用法\n\
"
)
    return reply_msg



def determine_functions(msg:str):
    # recognize the command name
    command = msg.split(sep='\n')
    command_name = command[0]
    # print("command name:", command_name)
    # print("msg:", msg)

    reply_msg = ''
    key = ''
    url = ''
    
    try:
        # key = r'{"type":"service_account","project_id":"majestic-lodge-394107","private_key_id":"cdddd4872e4d8c48a0fd2a0986bb529ca1f42519","private_key":"-----BEGIN PRIVATE KEY-----\nMIIEvQIBADANBgkqhkiG9w0BAQEFAASCBKcwggSjAgEAAoIBAQCq8RuVoLFOSzKU\neuj6iM7IPmaVjYqySyhEKr9zusHxNZE7UpGhBr/mMr3JwYViRlTSLOvI3n74KT1m\nJjzpNjZQWFPjWsUaSCdpIQ99w+H/spqViDkanNlPm68DH1Oy1ArJFT3DCfKDlrza\nYyUCUw59j44W06elnWZlEawIGELMiU795FlMSYxEFFS0K5cQ2a4I4Q/OpvK9/niS\nF8xNIgKPiBkMIc5nDNR6h+78lbkC1h7EbvSOwSG99mrPq2b3f5VWV93ZAuhSA1vn\nB8D8tchtNINJfaM8NOzhqkdQYoSRrEWK20gUmTQyrvP9flsJJDt89w4KRTbnM1Be\nR0qs3q17AgMBAAECggEATPcU/+gjnMhPxDmY12Cslc0+u/xII+GiBhsnK1C9jMCd\nHNQe3J0g3uEewY3f4/EdtKnkGYNQMKTEz87MowY1KzSxxI50a1JsaDGp+2qsQUfl\nwQjeCSTw1R6YDHRY544AMyxcrAm5BtViP4PfQG4r+o2doJp4g6FcXoo35kciIFu+\nix35S9eFn+urmBcWDOJAVjBtrfZpC1BivCkAdPdiKQPwJsxoUu9TtVMf9iDvNhhf\ncbbk/cGiY1c2ZMgmGhgPMWBQQasx+gxpnc52hhOjzNPDrYRh4RJXCx/rISY9geVU\n3W21ZzO28u490WIOfTuuzmFEAmW/6nhqU6Oz4bCW0QKBgQDsaFsQ/pshMbUjjRYq\n9seJmlqmpyxlHSGsruZ4zUMQuS4keXWb7DL4ypXWhvgpndSoRskSwqRcBsOxVAbq\nw+VypyclrwHM3DzQ1OvYEBbaTiQkz31ZtY46PR4J7k//c2T4sYuY8CxbOJsKdrfY\n83cEMELUC+HZBse2gD4YzDt38QKBgQC5G9Lo95SPeK66Fq9XkQsVKbTkbLk49+X4\newDgGEVKoViR9BnWByvj+/17/WnpDut02a+pgxMMxTMvySNs8XGVHkDEtZohCnHA\n7HJlSWFxGGIPWeeVeVc0hgbdd7cUmMk2jeNNvYRB/uVAdxYeNynfkvofrtwLN2er\nGM9CB0IIKwKBgFOMGcrqv/Y+M+7peJEcf64wn6LP58+gOPtnIEpG+FGbsCPxzM+a\n7PSh28xiDKfggHwr7/myUhW3ykcMFBm5u4gGbL5TmAZHOzLuXJ8SKJFkFj/wGDOx\nBx+r48bMsvbrWB7P2C7nijV+zsQm6phAiqovSB7aSCnDzKbBsbBf1RBxAoGAafpN\nEQYV7uIoHvA36Qlob/BV2WWJ0dzTtCQwBxy+JxEi1UUMuaWXckpmAOPADCd3lInA\n8WrSsEACozwj5Q6Ced49NKHIIVyKbeqxP934RLiyA5n0ZXZ3/+Ev8wHENq2WnX40\ngeCb5PDbLcJAToJEnfTW8Oa6ok1RM/rbRjFDk8sCgYEA1CjmQ9xT+u3+CRyKMJzs\nnoJMSGkIfgGyejWTZAhK7gbDmFNLl1OUwtfFaonk6aqIU9+hOiI2c0/N1Zy6Zsdg\nn0ynGC1DH0iOBpX1Er4+h1U73x2oYos1bN6PUT4s3kSaTo6Bn/WDKjI64jVi4nk7\n80rMCNAugu2sorZCw1TG66w=\n-----END PRIVATE KEY-----\n","client_email":"my-line-bot-service@majestic-lodge-394107.iam.gserviceaccount.com","client_id":"116040915155022016894","auth_uri":"https://accounts.google.com/o/oauth2/auth","token_uri":"https://oauth2.googleapis.com/token","auth_provider_x509_cert_url":"https://www.googleapis.com/oauth2/v1/certs","client_x509_cert_url":"https://www.googleapis.com/robot/v1/metadata/x509/my-line-bot-service%40majestic-lodge-394107.iam.gserviceaccount.com","universe_domain":"googleapis.com"}'
        # url = "https://docs.google.com/spreadsheets/d/1CCZnka0AEZz2WyiniWXyGUAqMfKW17vNSpZ5g4qCp6w/edit?hl=zh-TW#gid=0"
        
        key = r'{"type": "service_account","project_id": "majestic-lodge-394107","private_key_id": "cdddd4872e4d8c48a0fd2a0986bb529ca1f42519","private_key": "-----BEGIN PRIVATE KEY-----\nMIIEvQIBADANBgkqhkiG9w0BAQEFAASCBKcwggSjAgEAAoIBAQCq8RuVoLFOSzKU\neuj6iM7IPmaVjYqySyhEKr9zusHxNZE7UpGhBr/mMr3JwYViRlTSLOvI3n74KT1m\nJjzpNjZQWFPjWsUaSCdpIQ99w+H/spqViDkanNlPm68DH1Oy1ArJFT3DCfKDlrza\nYyUCUw59j44W06elnWZlEawIGELMiU795FlMSYxEFFS0K5cQ2a4I4Q/OpvK9/niS\nF8xNIgKPiBkMIc5nDNR6h+78lbkC1h7EbvSOwSG99mrPq2b3f5VWV93ZAuhSA1vn\nB8D8tchtNINJfaM8NOzhqkdQYoSRrEWK20gUmTQyrvP9flsJJDt89w4KRTbnM1Be\nR0qs3q17AgMBAAECggEATPcU/+gjnMhPxDmY12Cslc0+u/xII+GiBhsnK1C9jMCd\nHNQe3J0g3uEewY3f4/EdtKnkGYNQMKTEz87MowY1KzSxxI50a1JsaDGp+2qsQUfl\nwQjeCSTw1R6YDHRY544AMyxcrAm5BtViP4PfQG4r+o2doJp4g6FcXoo35kciIFu+\nix35S9eFn+urmBcWDOJAVjBtrfZpC1BivCkAdPdiKQPwJsxoUu9TtVMf9iDvNhhf\ncbbk/cGiY1c2ZMgmGhgPMWBQQasx+gxpnc52hhOjzNPDrYRh4RJXCx/rISY9geVU\n3W21ZzO28u490WIOfTuuzmFEAmW/6nhqU6Oz4bCW0QKBgQDsaFsQ/pshMbUjjRYq\n9seJmlqmpyxlHSGsruZ4zUMQuS4keXWb7DL4ypXWhvgpndSoRskSwqRcBsOxVAbq\nw+VypyclrwHM3DzQ1OvYEBbaTiQkz31ZtY46PR4J7k//c2T4sYuY8CxbOJsKdrfY\n83cEMELUC+HZBse2gD4YzDt38QKBgQC5G9Lo95SPeK66Fq9XkQsVKbTkbLk49+X4\newDgGEVKoViR9BnWByvj+/17/WnpDut02a+pgxMMxTMvySNs8XGVHkDEtZohCnHA\n7HJlSWFxGGIPWeeVeVc0hgbdd7cUmMk2jeNNvYRB/uVAdxYeNynfkvofrtwLN2er\nGM9CB0IIKwKBgFOMGcrqv/Y+M+7peJEcf64wn6LP58+gOPtnIEpG+FGbsCPxzM+a\n7PSh28xiDKfggHwr7/myUhW3ykcMFBm5u4gGbL5TmAZHOzLuXJ8SKJFkFj/wGDOx\nBx+r48bMsvbrWB7P2C7nijV+zsQm6phAiqovSB7aSCnDzKbBsbBf1RBxAoGAafpN\nEQYV7uIoHvA36Qlob/BV2WWJ0dzTtCQwBxy+JxEi1UUMuaWXckpmAOPADCd3lInA\n8WrSsEACozwj5Q6Ced49NKHIIVyKbeqxP934RLiyA5n0ZXZ3/+Ev8wHENq2WnX40\ngeCb5PDbLcJAToJEnfTW8Oa6ok1RM/rbRjFDk8sCgYEA1CjmQ9xT+u3+CRyKMJzs\nnoJMSGkIfgGyejWTZAhK7gbDmFNLl1OUwtfFaonk6aqIU9+hOiI2c0/N1Zy6Zsdg\nn0ynGC1DH0iOBpX1Er4+h1U73x2oYos1bN6PUT4s3kSaTo6Bn/WDKjI64jVi4nk7\n80rMCNAugu2sorZCw1TG66w=\n-----END PRIVATE KEY-----\n","client_email": "my-line-bot-service@majestic-lodge-394107.iam.gserviceaccount.com","client_id": "116040915155022016894","auth_uri": "https://accounts.google.com/o/oauth2/auth","token_uri": "https://oauth2.googleapis.com/token","auth_provider_x509_cert_url": "https://www.googleapis.com/oauth2/v1/certs","client_x509_cert_url": "https://www.googleapis.com/robot/v1/metadata/x509/my-line-bot-service%40majestic-lodge-394107.iam.gserviceaccount.com","universe_domain": "googleapis.com"}'
        url = "https://docs.google.com/spreadsheets/d/1CCZnka0AEZz2WyiniWXyGUAqMfKW17vNSpZ5g4qCp6w/edit?hl=zh-TW#gid=0"
        # key = os.environ.get("GOOGLE_SECRET_KEY")
        # url = os.environ.get("GOOGLE_SHEET_URL_LEARNINGBOT")
    except:
        reply_msg = "secret key or url not found"
        return reply_msg
    
    
    try:
        if command_name in ["#抽 help", "#pick help"]:
            ep = ElementPicker()
            reply_msg += ep.help()
        elif command_name in ["#抽", "# 抽", "#pick", "# pick"]:
            ep = ElementPicker()
            reply_msg += ep.main(command[1:])

        
        
        elif command_name in ["#學習 help", "#learn help"]:
            lb = LearningBot(key, url)
            reply_msg += lb.help()
                
        elif command_name in ["#學習", "# 學習", "#learn", "# learn"]:
            lb = LearningBot(key, url)
            reply_msg += lb.main(user_question=command[1], new_answer=command[2], to_teach=True)
        
        elif msg[0] == ' ':
            lb = LearningBot(key, url)
            reply_msg += lb.main(msg[1:])

        
        else:
            reply_msg += "Unknow command"
    
    except:
        reply_msg += "Command format not CORRECT!\n指令格式不正確"
        
    return reply_msg


def test(times=10):
    '''
    For testing command name, not the ep.main() or lb.main() functions
    '''
    c = 0
    while c < times:
        c += 1
        
        msg = input("Enter the msg:\n")
        reply = determine_functions(msg)
        print(reply)



# print(show_commands())
# test(5)