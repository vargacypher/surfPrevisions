from flask import Flask, request, jsonify
from fetch_data import generate_data

app = Flask(__name__)



@app.route("/surf_data", methods=["GET"])
def get_tides():
    point = request.args.get("point", '5842041f4e65fad6a7708cfd')
    
    surf_data = generate_data(point)

    return jsonify(surf_data.__dict__)


if __name__ == '__main__':
    app.run()
