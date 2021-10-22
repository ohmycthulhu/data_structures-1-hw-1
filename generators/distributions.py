from scipy.stats import t, chi2, f
from writers import UsualWriter, ComplexWriter

class Distribution:
    def __init__(self, params):
        pass

    @staticmethod
    def resolve(alg, params):
        if alg == 't':
            return TDistribution(params)
        elif alg == 'chi':
            return ChiDistribution(params)
        elif alg == 'f':
            return FDistribution(params)
        return None

    @staticmethod
    def available_algorithms():
        return '''
            t for Student T distribution
            chi for Chi-square distribution
            f for F distribution
        '''

    def validate(self):
        return False

    @staticmethod
    def error_message():
        return 'You should provide max df for generating'

    def calculate(self):
        return [], [], [[]]

    def writer(self, path):
        return UsualWriter(path)


class TDistribution(Distribution):
    def __init__(self, params):
        super().__init__(params)
        self.min_t = 1
        self.max_t = int(params[0]) if len(params) >= 1 else None
        self.alphas = self.default_alphas()

    @staticmethod
    def default_alphas():
        return [0.4, 0.25, 0.1, 0.05, 0.025, 0.01, 0.005, 0.0005]

    def validate(self):
        return self.max_t is not None and self.max_t > self.min_t

    @staticmethod
    def error_message():
        return 'You should provide max df for generating'

    def calculate(self):
        rows = [i for i in range(self.min_t, self.max_t + 1)]
        cols = self.alphas

        values = [[self._calculate_cell(alpha, df) for alpha in cols] for df in rows]

        return {'rows': rows, 'cols': cols, 'values': values}

    @staticmethod
    def _calculate_cell(alpha, df):
        return t.ppf(1 - alpha, df)


class ChiDistribution(TDistribution):
    @staticmethod
    def _calculate_cell(alpha, df):
        return chi2.ppf(1 - alpha, df)

    @staticmethod
    def default_alphas():
        return [0.995, 0.975, 0.2, 0.1, 0.05, 0.025, 0.02, 0.01, 0.005]


class FDistribution(Distribution):
    def __init__(self, params):
        super().__init__(params)
        self.df1_min, self.df2_min = 1, 1
        self.df1_max, self.df2_max = [int(p) for p in params] if len(params) >= 2 else [None, None]
        self.alphas = self.default_alphas()

    @staticmethod
    def default_alphas():
        return [0.9, 0.5, 0.1]

    def validate(self):
        if self.df2_max is None or self.df1_max is None:
            return False
        return self.df2_max > self.df2_min and self.df1_max > self.df1_min

    @staticmethod
    def error_message():
        return 'You should provide max df1 and max df2 for generating'

    def calculate(self):
        rows = [i for i in range(self.df2_min, self.df2_max + 1)]
        cols = [i for i in range(self.df1_min, self.df2_max + 1)]
        indices = self.alphas

        values = [
            [
                [self._calculate_cell(alpha, df1, df2) for df1 in cols]
                for df2 in rows
            ]
            for alpha in indices
        ]

        return {'rows': rows, 'cols': cols, 'indices': indices, 'values': values}

    @staticmethod
    def _calculate_cell(alpha, df1, df2):
        return f.ppf(1 - alpha, df1, df2)

    def writer(self, path):
        return ComplexWriter(path)
