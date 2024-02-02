import json 
from api.fetch_data import generate_data

if __name__ == "__main__":
    surf_data = generate_data('5842041f4e65fad6a7708cfd')
    with open('barrinha.json', 'w') as f:
        json.dump(surf_data.__dict__, f)
