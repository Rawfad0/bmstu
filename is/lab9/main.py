import sys
import hashlib
from cryptography.hazmat.primitives import hashes, serialization
from cryptography.hazmat.primitives.asymmetric import rsa, padding
from cryptography.hazmat.backends import default_backend


# ---------- PDF ----------
def read_pdf(path):
    with open(path, "rb") as f:
        return f.read()


# ---------- HASH ----------
def hash_pdf(data):
    sha256 = hashlib.sha256()
    sha256.update(data)
    return sha256.digest()


# ---------- KEYS ----------
def generate_rsa_keys():
    private_key = rsa.generate_private_key(
        public_exponent=65537,
        key_size=2048,
        backend=default_backend()
    )
    return private_key, private_key.public_key()


def save_private_key(private_key, filename="private_key.pem"):
    with open(filename, "wb") as f:
        f.write(
            private_key.private_bytes(
                encoding=serialization.Encoding.PEM,
                format=serialization.PrivateFormat.PKCS8,
                encryption_algorithm=serialization.NoEncryption()
            )
        )


def save_public_key(public_key, filename="public_key.pem"):
    with open(filename, "wb") as f:
        f.write(
            public_key.public_bytes(
                encoding=serialization.Encoding.PEM,
                format=serialization.PublicFormat.SubjectPublicKeyInfo
            )
        )


def load_public_key(filename="public_key.pem"):
    with open(filename, "rb") as f:
        return serialization.load_pem_public_key(
            f.read(),
            backend=default_backend()
        )


# ---------- SIGNATURE ----------
def sign_hash(private_key, hash_bytes):
    return private_key.sign(
        hash_bytes,
        padding.PSS(
            mgf=padding.MGF1(hashes.SHA256()),
            salt_length=padding.PSS.MAX_LENGTH
        ),
        hashes.SHA256()
    )


def save_signature(signature, filename="signature.bin"):
    with open(filename, "wb") as f:
        f.write(signature)


def load_signature(filename="signature.bin"):
    with open(filename, "rb") as f:
        return f.read()


def verify_signature(public_key, signature, hash_bytes):
    try:
        public_key.verify(
            signature,
            hash_bytes,
            padding.PSS(
                mgf=padding.MGF1(hashes.SHA256()),
                salt_length=padding.PSS.MAX_LENGTH
            ),
            hashes.SHA256()
        )
        return True
    except Exception:
        return False


# ================== MAIN ==================
if __name__ == "__main__":

    if len(sys.argv) != 3:
        print("Использование:")
        print("  python sign_pdf.py -e <file.pdf>   # создать ЭЦП")
        print("  python sign_pdf.py -d <file.pdf>   # проверить ЭЦП")
        sys.exit(1)

    mode = sys.argv[1]
    pdf_path = sys.argv[2]

    pdf_data = read_pdf(pdf_path)
    pdf_hash = hash_pdf(pdf_data)

    if mode == "-e":
        private_key, public_key = generate_rsa_keys()
        signature = sign_hash(private_key, pdf_hash)

        save_private_key(private_key)
        save_public_key(public_key)
        save_signature(signature)

    elif mode == "-d":

        public_key = load_public_key()
        signature = load_signature()

        valid = verify_signature(public_key, signature, pdf_hash)

        print("Подпись корректна:", valid)

    else:
        print("Неизвестный режим:", mode)
