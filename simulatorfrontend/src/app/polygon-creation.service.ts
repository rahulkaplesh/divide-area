import { EventEmitter, Injectable } from '@angular/core';

import { Area } from './typings';


@Injectable({
  providedIn: 'root'
})
export class PolygonCreationService {

  areaList: Area[] = [];

  areaListChange: EventEmitter<Area[]> = new EventEmitter();
  areaSelectionChange: EventEmitter<Area> = new EventEmitter();

  constructor() { }

  addArea(): void {
    let name: string = `Area-${this.areaList.length+1}`;
    let areaToPush: Area = {
      name,
      points: [],
      selected: false
    }
    this.areaList = [...this.areaList, areaToPush];
    this.areaListChange.emit(this.areaList);
  }

  getAreaListChangeEmitter(): EventEmitter<Area[]> {
    return this.areaListChange;
  }

  selectedAreaChanged(selectedArea: Area) {
    this.areaSelectionChange.emit(selectedArea);
  }

  getAreaSelectionChangeEmitter(): EventEmitter<Area> {
    return this.areaSelectionChange;
  }
}
