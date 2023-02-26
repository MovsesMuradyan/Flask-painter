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
    file.save(os.path.join('files', filename))
    input_file_path = os.path.join('files', filename)
    grayscale_file_path = os.path.join('files', 'grayscale_file')
    output_file_path = os.path.join('download', 'output.txt')
    cmd = f'.\painter.exe "{input_file_path}" "{grayscale_file_path}" > "{output_file_path}"'
    os.system(cmd)
    return render_template("index.html")

@app.route("/download")
def download():
    return send_file("download/output.txt", as_attachment=True)

if __name__ == '__main__':
    app.run(debug=True)