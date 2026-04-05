from fastapi import FastAPI, Query
from typing import Optional
from datetime import date

app = FastAPI()


@app.get("/hotels/{hotels_id}")
def get_hotels(
	location: str,
	data_in: date,
	date_out: date,
	cookie: Optional[bool] = None,
	stars: Optional[int] = Query(None, ge=1, le=5)
):

return "Succeses"