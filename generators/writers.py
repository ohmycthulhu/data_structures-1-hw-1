import math

class Writer:
    def __init__(self, path):
        self.path = path

    def write(self, data):
        pass


class UsualWriter(Writer):
    def write(self, data):
        with open(self.path, 'w') as file:
            self.write_headers(file, data)
            self.write_content(file, data)

    def write_headers(self, file, data):
        cols = data['cols']
        file.write(';' + ';'.join([str(c) for c in cols]) + '\n')

    def write_content(self, file, data):
        rows = data['rows']
        values = data['values']

        for i, row in enumerate(rows):
            file.write(';'.join([str(row)] + [str(n) for n in values[i]]))
            file.write('\n')


class ComplexWriter(Writer):
    def write(self, data):
        with open(self.path, 'w') as file:
            self.write_header(file, data)
            self.write_separator(file, data)
            self.write_content(file, data)

    def write_header(self, file, data):
        cols = data['cols']
        file.write('p;;' + ';'.join([str(c) for c in cols]) + '\n')

    def write_separator(self, file, data):
        cols = data['cols']
        file.write('n;x' + ';' * len(cols))
        file.write('\n')

    def write_content(self, file, data):
        rows, indices, content = data['rows'], data['indices'], data['values']
        for i, index in enumerate(indices):
            self.write_table(file, rows, content[i], math.floor(i + 1))

    def write_table(self, file, rows, content, index):
        file.write(f"{index}")
        for i, row in enumerate(rows):
            file.write(f";{row};{';'.join([str(j) for j in content[i]])}\n")

