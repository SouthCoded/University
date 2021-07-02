from flask import Flask, render_template, request
import boto3
import datetime
import json
import csv

# EB looks for an 'application' callable by default.
application = Flask(__name__)


@application.route('/')
def index():
	filename = 'logfile' + datetime.datetime.now().strftime("%y%m%d_%H%M%S")
	return render_template('index.html',data=filename)

@application.route('/send-data')
def send_data():
	width = request.args.get('width')
	height = request.args.get('height')
	offset = request.args.get('offset')
	pixelDepth = request.args.get('pixel')
	colorDepth = request.args.get('colorDepth')
	filename = request.args.get('filename')

	s3 = boto3.resource(service_name='s3',region_name='eu-west-2',aws_access_key_id='',aws_secret_access_key='')
	
	temp = dict(request.headers)
	request_format = json.dumps(temp)

	dct = {'headers':request_format,'width':width,'height':height,'offset':offset,'pixelDepth':pixelDepth,'colorDepth':colorDepth,'filename':filename}

	fullfilename = filename + '.csv'
	
	with open(fullfilename, 'w') as f:  
		writer = csv.writer(f)
		for k, v in dct.items():
			if 'filename' not in k:
				writer.writerow([k, v])

	print(fullfilename)
	s3.Bucket('dissdata').upload_file(Filename=fullfilename, Key=fullfilename)
	return render_template('sendingdata.html')

# run the app.
if __name__ == "__main__":
    # Setting debug to True enables debug output. This line should be
    # removed before deploying a production app.
    application.debug = True
    application.run()
