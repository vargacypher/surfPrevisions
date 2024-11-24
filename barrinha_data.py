import json 
from api.fetch_data import generate_data

if __name__ == "__main__":
    surf_data = generate_data('640a5822b6d769477c573bf3')
    with open('barrinha.json', 'w') as f:
        json.dump(surf_data.__dict__, f)
