from dotenv import load_dotenv
import os
import pymongo
import pprint
import time

load_dotenv()

class DB:

    def __init__(self, db_name):
        self.db_name = db_name
        self.__password = os.environ.get('password')
        self.__username = os.environ.get('username')

    def connect_db(self):
        # Replace the uri string with your MongoDB deployment's connection string.
        conn_str = f"mongodb+srv://{self.__username}:{self.__password}@search-engine.h1yhbwf.mongodb.net/?retryWrites=true&w=majority"

        # Connect to your local database
        # client = pymongo.MongoClient('localhost', 27017)

        # Set a 5-second connection timeout
        client = pymongo.MongoClient(conn_str, serverSelectionTimeoutMS=5000)

        try:
            client.server_info()
        except Exception:
            print("Unable to connect to the server.")

        # Getting a Database
        db = client[self.db_name]
        return db

    def create_collection(self, collection_name: str):
        db = self.connect_db()
        collection = db[collection_name]
        return collection

    def post_db(self, dataset_path: str, collection_name: str):

        db = self.connect_db()

        num_lines = sum(1 for _ in open(dataset_path))
        with open(dataset_path) as f:
            lines = f.readlines()

        ids_texts = {}
        i, j = 0, 1
        for i in range(num_lines):
            time.sleep(0.05)
            if (lines[i][j+1] != " "):
                j += 1
            ids_texts[lines[i][:j+1]] = lines[i][j+1:]
            # print(lines[i][:j+1])
            # print(lines[i][j+1:])

        collection = db[collection_name]
        for key in ids_texts:
            post = {"_id": key, "text": ids_texts[key]}
            collection.insert_one(post)

    def get_by_did(self, _id: str, collection_name: str):
        db = self.connect_db()
        collection = db[collection_name]
        collection.find_one({"id": _id})

    def print(self, _id: str, collection_name: str):
        db = self.connect_db()
        collection = db[collection_name]
        pprint.pprint(collection.find_one({"_id": _id}))
