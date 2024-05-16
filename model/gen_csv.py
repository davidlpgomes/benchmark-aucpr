"""Generate a CSV file the model's scores and y_true."""

import argparse

from river import datasets
from river import tree
from tqdm import tqdm


def main(output_csv: str) -> None:
    """Runs the stream and creates the CSV file"""
    X_y = datasets.MaliciousURL()
    model = tree.HoeffdingTreeClassifier()

    print('Running stream with the MaliciousURL dataset...')

    f = open(output_csv, 'w')
    f.write('y_score,y_true\n')

    for x, y in tqdm(X_y, total=X_y.n_samples):
        score = model.predict_proba_one(x)
        model.learn_one(x, y)

        score = score[True] if True in score else 0

        f.write(f'{score:.4f},{int(y)}\n')

    f.close()


if __name__ == '__main__':
    parser = argparse.ArgumentParser(
        description='Run a stream and save the y_true and y_score'
    )

    parser.add_argument(
        '-o',
        '--output_csv',
        type=str,
        required=True,
        help='Path to save the CSV file'
    )

    args = parser.parse_args()

    main(args.output_csv)
