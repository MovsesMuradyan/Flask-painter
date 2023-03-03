from flask import Flask, render_template, request, redirect, send_file
import os

app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/receive", methods=["POST"])
def receive():
    file = request.files['file']
    filename = file.filename
    file.save(os.path.join('./Upload', filename))
    input_file_path = os.path.join('./Upload', filename)
    output_file_path = os.path.join('./Download', 'output.txt')
    cmd = f'./C/painter -i "{input_file_path}" -o "{output_file_path}"'
    os.system(cmd)
    return render_template("download.html")

@app.route("/download")
def download():
    return send_file("Download/output.txt", as_attachment=True)

if __name__ == '__main__':
    app.run(debug=True)