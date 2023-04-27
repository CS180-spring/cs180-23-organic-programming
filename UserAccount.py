class UserAccount:
    def __init__(self, username, password):
        self.username = username
        self.password = password

    def setUsername(self, username):
        self.username = username

    def setPassword(self, password):
        self.password = password

    def getUsername(self):
        return self.username

    def getPassword(self):
        return self.password