FROM python:3.10
EXPOSE 8080
WORKDIR /app
RUN pip3 install pysurfline
RUN pip3 install flask gunicorn
COPY main.py .
CMD ["gunicorn", "--bind", "0.0.0.0:8080", "--workers", "2", "app:main"]
