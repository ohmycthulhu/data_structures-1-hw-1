import sys
from distributions import Distribution


def main():
    if len(sys.argv) < 3:
        print('You should specify output file and an algorithm')
        print(Distribution.available_algorithms())
        return

    _, output_file, alg_keyword, *params = sys.argv

    alg = Distribution.resolve(alg_keyword, params)

    if alg is None:
        print('Algorithm doesn\'t exist')
        return

    if not alg.validate():
        print(alg.error_message())
        return

    data = alg.calculate()
    alg.writer(output_file).write(data)



if __name__ == '__main__':
    main()
