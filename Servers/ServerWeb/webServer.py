from http.server import BaseHTTPRequestHandler, HTTPServer
import urllib 
from urllib.parse import *
import os

# HTTPRequestHandler class
class HTTPServer_RequestHandler(BaseHTTPRequestHandler):

    def _set_headers(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()

    def doPathParse(self,path):
        parsePath = urlparse(path)
        filePath = parsePath.path
        fileQuery = parsePath.query
        fileDecode = urllib.parse.parse_qs(fileQuery)
        result = {"parse":parsePath, "path":filePath , "query": fileQuery, "decodeQuery": fileDecode}
        return result


    def convertDict(self, path):
        dataURL = self.doPathParse(path)['path']
        head_tail = os.path.split(dataURL)
        param = head_tail[1]
        data = param.replace('&',' ')
        dataList = data.split(' ')
        dictParam = {}

        for m in dataList:
            cad = m.split('=')

            if cad[0]=='name':
                dictParam['name'] = cad[1]
            if cad[0]== 'last':
                dictParam['last'] = cad[1]
        return dictParam

    def do_POST(self):
        path = self.path
        print (self.convertDict(path)['name'])

        self._set_headers()
        self.wfile.write(bytes("ok","UTF-8"))


def run(server_class=HTTPServer, handler_class=HTTPServer_RequestHandler):
    print('starting server...')
    server_address = ('localhost', 8081)
    httpd = server_class(server_address, HTTPServer_RequestHandler)
    print('running server...')
    httpd.serve_forever()

if __name__ == '__main__':
    run()